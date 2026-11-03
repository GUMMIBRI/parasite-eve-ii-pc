// Make an original-compatible PS1 card from a native save without rewriting
// its contents. Link against the locally built DuckStation core/common/util
// using the regtest target's flags/libraries, replacing its frontend object.
#include "common/types.h"
#include "common/error.h"
#include "core/memory_card_image.h"

#include <algorithm>
#include <cstdio>
#include <filesystem>
#include <fstream>
#include <iterator>
#include <string_view>
#include <vector>

// The image library uses host translation for error messages; this command
// line utility has no translated UI.
namespace Host::Internal {
s32 GetTranslatedStringImpl(std::string_view, std::string_view message,
                           std::string_view, char* buffer, size_t capacity)
{
    if (message.size() > capacity) return -1;
    std::copy(message.begin(), message.end(), buffer);
    return static_cast<s32>(message.size());
}
}

int main(int argc, char** argv)
{
    if (argc != 3) {
        std::fprintf(stderr, "usage: export_card_image native-save new-card.mcd\n");
        return 2;
    }
    if (std::filesystem::exists(argv[2])) {
        std::fprintf(stderr, "output already exists: %s\n", argv[2]);
        return 2;
    }
    std::ifstream input(argv[1], std::ios::binary);
    if (!input) {
        std::fprintf(stderr, "cannot read save: %s\n", argv[1]);
        return 3;
    }
    std::vector<u8> bytes((std::istreambuf_iterator<char>(input)), {});
    MemoryCardImage::DataArray card;
    MemoryCardImage::Format(&card);
    Error error;
    const std::string filename = std::filesystem::path(argv[1]).filename().string();
    if (!MemoryCardImage::WriteFile(&card, filename, bytes, &error) ||
        !MemoryCardImage::SaveToFile(card, argv[2], &error)) {
        std::fprintf(stderr, "%s\n", error.GetDescription().c_str());
        return 4;
    }
    const auto files = MemoryCardImage::EnumerateFiles(card, false);
    std::vector<u8> restored;
    if (files.size() != 1 || files[0].filename != filename ||
        !MemoryCardImage::ReadFile(card, files[0], &restored, &error) || restored != bytes) {
        std::fprintf(stderr, "exported save verification failed\n");
        return 5;
    }
    std::printf("PS1 card: %s, save=%s, bytes=%u, free blocks=%u\n", argv[2],
                filename.c_str(), files[0].size, MemoryCardImage::GetFreeBlockCount(card));
}
