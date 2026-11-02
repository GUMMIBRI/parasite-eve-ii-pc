cmake_minimum_required(VERSION 3.21..3.31)
if(CMAKE_HOST_APPLE AND NOT DEFINED CMAKE_OSX_DEPLOYMENT_TARGET
   AND (NOT DEFINED CMAKE_SYSTEM_NAME OR CMAKE_SYSTEM_NAME STREQUAL "Darwin"))
    set(CMAKE_OSX_DEPLOYMENT_TARGET "15.0" CACHE STRING "Minimum supported macOS version")
endif()
project(parasite-eve-ii-pc VERSION 0.0.1 LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)

# PsyZ: our fork of the PsyZ PSY-Q replacement (SDL3 video/audio/input, libgte, libcd, MDEC).
set(PSYZ_DIR ${CMAKE_CURRENT_SOURCE_DIR}/third_party/psyz)
add_subdirectory(${PSYZ_DIR}/psyz ${CMAKE_CURRENT_BINARY_DIR}/psyz)
target_compile_definitions(psyz PRIVATE __psyz)

if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
    # The original task/actor workspaces are accessed through several layout views.
    add_compile_options("$<$<COMPILE_LANGUAGE:C>:-fno-strict-aliasing>"
        "$<$<COMPILE_LANGUAGE:C>:-ffunction-sections>"
        "$<$<COMPILE_LANGUAGE:C>:-fdata-sections>")
endif()

# The game proper (the former decompilation sources), compiled for the host.
file(GLOB GAME_MAIN_SOURCES CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/gameplay/*.c)
# main.c only switches to the PS1 boot stack; the port entry (src/port/main.c) replaces it.
list(FILTER GAME_MAIN_SOURCES EXCLUDE REGEX "/src/main/main\\.c$")
add_library(game_main OBJECT ${GAME_MAIN_SOURCES})
target_include_directories(game_main PUBLIC include include/decomp
    ${CMAKE_CURRENT_SOURCE_DIR}/build/include)
target_compile_definitions(game_main PUBLIC __psyz SKIP_ASM)
target_compile_options(game_main PRIVATE -w -Wno-incompatible-function-pointer-types -g -fno-omit-frame-pointer -include port/gpu_len.h)
target_link_libraries(game_main PUBLIC psyz)

# Overlay packages linked into the executable. The PS1 game swaps overlay code in and out of one address range;
# on the host a package is compiled in and its names resolve at link time. Packages share global names
# (docs/PORT_PLAN.md), so only the packages listed here are linked; add one when the game first needs it.
set(PE_PACKAGES
    src/title/title.c;src/mapui/map_dryfield/map_dryfield.c;src/mapui/map_dryfield_full/map_dryfield_full.c;src/mapui/map_neo_ark/map_neo_ark.c;src/mapui/map_shelter/map_shelter.c
    CACHE STRING "Overlay sources linked into the executable")
option(PE_EMBED_ASSETS "Comparison build: keep the build-time asset includes instead of loading from the disc" OFF)
if(PE_EMBED_ASSETS)
    add_compile_definitions(PE_EMBED_ASSETS=1)
endif()
option(PE_ALL_OVERLAYS "Compile every overlay package that builds on the host (experimental; does not link)" OFF)
if(PE_ALL_OVERLAYS)
    include(cmake/overlay_sources.cmake)
    set(PE_OVERLAY_LIST ${PE_OVERLAY_SOURCES})
else()
    set(PE_OVERLAY_LIST)
    foreach(src ${PE_PACKAGES})
        list(APPEND PE_OVERLAY_LIST ${CMAKE_CURRENT_SOURCE_DIR}/${src})
    endforeach()
endif()
if(NOT PE_ALL_OVERLAYS)
    list(APPEND PE_OVERLAY_LIST
        ${CMAKE_CURRENT_SOURCE_DIR}/src/aya/game_over/game_over.c
        ${CMAKE_CURRENT_SOURCE_DIR}/src/weapons/m93r/m93r.c
        ${CMAKE_CURRENT_SOURCE_DIR}/src/weapons/tonfa_baton/tonfa_baton.c
        ${CMAKE_CURRENT_SOURCE_DIR}/src/stages/akropolis/stage.c
        ${CMAKE_CURRENT_SOURCE_DIR}/src/stages/akropolis/rooms/mist_shooting_gallery/mist_shooting_gallery.c
        ${CMAKE_CURRENT_SOURCE_DIR}/src/stages/akropolis/rooms/mist_shooting_gallery/mist_shooting_gallery_courses.c
        ${CMAKE_CURRENT_SOURCE_DIR}/src/stages/akropolis/actors/shooting_gallery_pierce/shooting_gallery_pierce.c
        ${CMAKE_CURRENT_SOURCE_DIR}/src/stages/akropolis/actors/shooting_gallery_pierce/shooting_gallery_pierce_gallery.c
        ${CMAKE_CURRENT_SOURCE_DIR}/src/stages/akropolis/actors/shooting_gallery_targets/shooting_gallery_targets.c
        ${CMAKE_CURRENT_SOURCE_DIR}/src/stages/akropolis/rooms/plaza/plaza.c
        ${CMAKE_CURRENT_SOURCE_DIR}/src/stages/akropolis/rooms/west_elevator_hall/west_elevator_hall.c
        ${CMAKE_CURRENT_SOURCE_DIR}/src/stages/akropolis/rooms/east_elevator_hall/east_elevator_hall.c
        ${CMAKE_CURRENT_SOURCE_DIR}/src/stages/akropolis/actors/east_elevator_hall_swat_member/east_elevator_hall_swat_member.c
        ${CMAKE_CURRENT_SOURCE_DIR}/src/stages/akropolis/rooms/square/square.c
        ${CMAKE_CURRENT_SOURCE_DIR}/src/stages/akropolis/rooms/patio/patio.c
        ${CMAKE_CURRENT_SOURCE_DIR}/src/stages/akropolis/rooms/hallway/hallway.c
        ${CMAKE_CURRENT_SOURCE_DIR}/src/stages/akropolis/rooms/security_room/security_room.c
        ${CMAKE_CURRENT_SOURCE_DIR}/src/stages/akropolis/actors/security_monitors/security_monitors.c
        ${CMAKE_CURRENT_SOURCE_DIR}/src/stages/akropolis/rooms/fountain/fountain.c
        ${CMAKE_CURRENT_SOURCE_DIR}/src/stages/akropolis/rooms/fountain/fountain_water.c
        ${CMAKE_CURRENT_SOURCE_DIR}/src/stages/akropolis/rooms/forked_road/forked_road.c
        ${CMAKE_CURRENT_SOURCE_DIR}/src/stages/akropolis/rooms/forked_road/forked_road_effects.c
        ${CMAKE_CURRENT_SOURCE_DIR}/src/stages/akropolis/rooms/observatory/observatory.c
        ${CMAKE_CURRENT_SOURCE_DIR}/src/stages/akropolis/rooms/observatory/observatory_effects.c
        ${CMAKE_CURRENT_SOURCE_DIR}/src/stages/akropolis/rooms/observatory/observatory_rides.c
        ${CMAKE_CURRENT_SOURCE_DIR}/src/stages/akropolis/rooms/promenade/promenade.c
        ${CMAKE_CURRENT_SOURCE_DIR}/src/stages/akropolis/rooms/sanctuary/sanctuary.c
        ${CMAKE_CURRENT_SOURCE_DIR}/src/stages/akropolis/rooms/roof_garden/roof_garden.c
        ${CMAKE_CURRENT_SOURCE_DIR}/src/stages/akropolis/rooms/bridge/bridge.c
        ${CMAKE_CURRENT_SOURCE_DIR}/src/stages/akropolis/rooms/fire_escape/fire_escape.c
        ${CMAKE_CURRENT_SOURCE_DIR}/src/enemies/stranger/lesser/lesser_stranger.c
        ${CMAKE_CURRENT_SOURCE_DIR}/src/pe/pyrokinesis/pyrokinesis.c
        ${CMAKE_CURRENT_SOURCE_DIR}/src/pe/healing/healing.c
        ${CMAKE_CURRENT_SOURCE_DIR}/src/stages/akropolis/actors/roof_garden_swat_member/roof_garden_swat_member.c
        ${CMAKE_CURRENT_SOURCE_DIR}/src/stages/akropolis/actors/sanctuary_no_9/sanctuary_no_9.c
        ${CMAKE_CURRENT_SOURCE_DIR}/src/actors/actor_210700/actor_210700.c
        ${CMAKE_CURRENT_SOURCE_DIR}/src/actors/actor_402200/actor_402200.c
        ${CMAKE_CURRENT_SOURCE_DIR}/src/actors/actor_04000/actor_04000.c
        ${CMAKE_CURRENT_SOURCE_DIR}/src/actors/actor_401300/actor_401300.c
        ${CMAKE_CURRENT_SOURCE_DIR}/src/stages/akropolis/rooms/cafeteria/cafeteria.c
        ${CMAKE_CURRENT_SOURCE_DIR}/src/stages/akropolis/rooms/cafeteria/cafeteria_effects.c
        ${CMAKE_CURRENT_SOURCE_DIR}/src/stages/akropolis/actors/cafeteria_boss_stranger/cafeteria_boss_stranger.c
        ${CMAKE_CURRENT_SOURCE_DIR}/src/actors/actor_202900/actor_202900.c
        ${CMAKE_CURRENT_SOURCE_DIR}/src/actors/actor_210600/actor_210600.c
        ${CMAKE_CURRENT_SOURCE_DIR}/src/actors/actor_210600/actor_210600_contacts.c
        ${CMAKE_CURRENT_SOURCE_DIR}/src/actors/actor_310600/actor_310600.c
        ${CMAKE_CURRENT_SOURCE_DIR}/src/actors/actor_401800/actor_401800.c
        ${CMAKE_CURRENT_SOURCE_DIR}/src/actors/actor_05700/actor_05700.c
        ${CMAKE_CURRENT_SOURCE_DIR}/src/stages/akropolis/actors/patio_swat_member/patio_swat_member.c
        ${CMAKE_CURRENT_SOURCE_DIR}/src/stages/akropolis/actors/patio_leaping_strangers/patio_leaping_strangers.c
        ${CMAKE_CURRENT_SOURCE_DIR}/src/actors/actor_00700/actor_00700.c
        ${CMAKE_CURRENT_SOURCE_DIR}/src/actors/actor_01500/actor_01500.c
        ${CMAKE_CURRENT_SOURCE_DIR}/src/actors/actor_02600/actor_02600.c
        ${CMAKE_CURRENT_SOURCE_DIR}/src/actors/actor_207200/actor_207200.c
        ${CMAKE_CURRENT_SOURCE_DIR}/src/actors/actor_207200/actor_207200_2.c
        ${CMAKE_CURRENT_SOURCE_DIR}/src/actors/actor_300700/actor_300700.c
        ${CMAKE_CURRENT_SOURCE_DIR}/src/actors/actor_300700/actor_300700_2.c
        ${CMAKE_CURRENT_SOURCE_DIR}/src/actors/actor_401000/actor_401000.c
        ${CMAKE_CURRENT_SOURCE_DIR}/src/stages/akropolis/actors/square_grinning_stranger/square_grinning_stranger.c
        ${CMAKE_CURRENT_SOURCE_DIR}/src/stages/akropolis/actors/police_officers/police_officers.c
        ${CMAKE_CURRENT_SOURCE_DIR}/src/stages/akropolis/rooms/mist_parking/mist_parking.c
        ${CMAKE_CURRENT_SOURCE_DIR}/src/stages/akropolis/rooms/mist_parking/mist_parking_scenes.c
        ${CMAKE_CURRENT_SOURCE_DIR}/src/stages/akropolis/rooms/mist_parking/mist_parking_conversation.c
        ${CMAKE_CURRENT_SOURCE_DIR}/src/stages/akropolis/rooms/mist_parking/mist_parking_glows.c
        ${CMAKE_CURRENT_SOURCE_DIR}/src/stages/akropolis/rooms/mist_parking/mist_parking_shop.c
        ${CMAKE_CURRENT_SOURCE_DIR}/src/stages/akropolis/actors/parking_pierce/parking_pierce.c
        ${CMAKE_CURRENT_SOURCE_DIR}/src/actors/actor_213100/actor_213100.c)
    list(REMOVE_DUPLICATES PE_OVERLAY_LIST)
endif()
# Each PS1 overlay owns animation symbols that share names in the console
# address space. Preserve each copy when those overlays coexist on the host.
set_property(SOURCE
    src/stages/akropolis/rooms/mist_parking/mist_parking.c
    src/stages/akropolis/rooms/mist_parking/mist_parking_conversation.c
    APPEND PROPERTY COMPILE_DEFINITIONS
    gAyaStandClip=gMistParkingAyaStandClip
    gAyaAnim07Clip=gMistParkingAyaAnim07Clip
    gAyaTalkClip=gMistParkingAyaTalkClip
    gAyaTalkStartClip=gMistParkingAyaTalkStartClip
    gAyaTalkEndClip=gMistParkingAyaTalkEndClip)
set_property(SOURCE src/stages/akropolis/rooms/square/square.c
    APPEND PROPERTY COMPILE_DEFINITIONS gRoomCutsceneSoundTask=gAkropolisSquareRoomCutsceneSoundTask)
set_property(SOURCE src/stages/akropolis/rooms/plaza/plaza.c
    APPEND PROPERTY COMPILE_DEFINITIONS gAyaIdleClip=gAkropolisPlazaAyaIdleClip)
set_property(SOURCE src/actors/actor_213100/actor_213100.c
    APPEND PROPERTY COMPILE_DEFINITIONS
    actorMsgPlaceEuler=jodieActorMsgPlaceEuler
    gAyaStandClip=gJodieAyaStandClip
    gAyaAnim07Clip=gJodieAyaAnim07Clip
    gAyaTalkClip=gJodieAyaTalkClip
    gAyaTalkStartClip=gJodieAyaTalkStartClip
    gAyaTalkEndClip=gJodieAyaTalkEndClip)
# Each retail package owns these exports; resident host overlays need distinct names.
set_property(SOURCE src/stages/akropolis/rooms/patio/patio.c
    APPEND PROPERTY COMPILE_DEFINITIONS
    gAyaStandClip=gAkropolisPatioAyaStandClip
    gShelterR47PlayerLookAtMapClip=gAkropolisPatioPlayerLookAtMapClip)
set_property(SOURCE src/stages/akropolis/actors/patio_leaping_strangers/patio_leaping_strangers.c
    APPEND PROPERTY COMPILE_DEFINITIONS actorMsgPlaceEuler=patioLeapingStrangersMsgPlaceEuler)
set_property(SOURCE src/actors/actor_401000/actor_401000.c
    APPEND PROPERTY COMPILE_DEFINITIONS
    actorMsgIsPresent=actor401000MsgIsPresent
    actorMsgPlaceRecordYaw=actor401000MsgPlaceRecordYaw
    actorMsgSetVisibility=actor401000MsgSetVisibility)
set_property(SOURCE src/actors/actor_300700/actor_300700.c src/actors/actor_300700/actor_300700_2.c
    APPEND PROPERTY COMPILE_DEFINITIONS
    gRatAndMothRatBody=gActor300700RatBody ratSpawn=actor300700RatSpawn)
set_property(SOURCE src/actors/actor_310600/actor_310600.c
    APPEND PROPERTY COMPILE_DEFINITIONS actorMsgPlaceEuler=actor310600MsgPlaceEuler)
set_property(SOURCE src/actors/actor_202900/actor_202900.c
    APPEND PROPERTY COMPILE_DEFINITIONS actorMsgSetPairVisibility=actor202900MsgSetPairVisibility)
set_property(SOURCE src/actors/actor_210600/actor_210600.c src/actors/actor_210600/actor_210600_contacts.c
    APPEND PROPERTY COMPILE_DEFINITIONS actorMsgPlace=actor210600MsgPlace)
set_property(SOURCE src/actors/actor_401800/actor_401800.c
    APPEND PROPERTY COMPILE_DEFINITIONS
    actorMsgIsPresent=actor401800MsgIsPresent
    actorMsgReleaseHold=actor401800MsgReleaseHold
    actorMsgPlaceRecordYaw=actor401800MsgPlaceRecordYaw
    actorMsgSetVisibility=actor401800MsgSetVisibility)
set_property(SOURCE src/stages/akropolis/rooms/cafeteria/cafeteria_effects.c
    APPEND PROPERTY COMPILE_DEFINITIONS ActorContact_ScratchPosition=gCafeteriaEffectsScratchPosition)
set_property(SOURCE src/stages/akropolis/actors/cafeteria_boss_stranger/cafeteria_boss_stranger.c
    APPEND PROPERTY COMPILE_DEFINITIONS ActorContact_ScratchPosition=gCafeteriaBossScratchPosition)
set_property(SOURCE src/stages/akropolis/rooms/hallway/hallway.c
    APPEND PROPERTY COMPILE_DEFINITIONS ActorContact_ScratchPosition=gAkropolisHallwayScratchPosition)
set_property(SOURCE src/stages/akropolis/rooms/security_room/security_room.c
    APPEND PROPERTY COMPILE_DEFINITIONS ActorContact_ScratchPosition=gAkropolisSecurityRoomScratchPosition)
set_property(SOURCE src/stages/akropolis/rooms/sanctuary/sanctuary.c
    APPEND PROPERTY COMPILE_DEFINITIONS ActorContact_ScratchPosition=gAkropolisSanctuaryScratchPosition)
set_property(SOURCE src/stages/akropolis/rooms/roof_garden/roof_garden.c
    APPEND PROPERTY COMPILE_DEFINITIONS
    ActorContact_ScratchPosition=gAkropolisRoofGardenScratchPosition
    gAyaStandClip=gAkropolisRoofGardenAyaStandClip)
set_property(SOURCE src/stages/akropolis/actors/roof_garden_swat_member/roof_garden_swat_member.c
    APPEND PROPERTY COMPILE_DEFINITIONS actorMsgSetPairVisibility=roofGardenSwatMsgSetPairVisibility)
set_property(SOURCE src/stages/akropolis/rooms/forked_road/forked_road_effects.c
    APPEND PROPERTY COMPILE_DEFINITIONS gAyaStandClip=gAkropolisForkedRoadAyaStandClip)
set_property(SOURCE src/actors/actor_401300/actor_401300.c
    APPEND PROPERTY COMPILE_DEFINITIONS
    actorMsgIsPresent=actor401300MsgIsPresent
    actorMsgReleaseHold=actor401300MsgReleaseHold
    actorMsgSetVisibility=actor401300MsgSetVisibility
    ActorContact_ScratchPosition=gActor401300ScratchPosition)
set_property(SOURCE src/actors/actor_04000/actor_04000.c
    APPEND PROPERTY COMPILE_DEFINITIONS actorMsgPlace=actor04000MsgPlace)
set_property(SOURCE src/actors/actor_402200/actor_402200.c
    APPEND PROPERTY COMPILE_DEFINITIONS
    gGolemStaggerClip=gActor402200GolemStaggerClip
    gGolemIdleClip=gActor402200GolemIdleClip)
set_property(SOURCE src/weapons/tonfa_baton/tonfa_baton.c
    APPEND PROPERTY COMPILE_DEFINITIONS gAyaIdleClip=gTonfaBatonAyaIdleClip)
set_property(SOURCE src/actors/actor_00700/actor_00700.c
    APPEND PROPERTY COMPILE_OPTIONS -include ${CMAKE_CURRENT_SOURCE_DIR}/cmake/aliases/actor_200700__actor_00700.h)
add_library(game_overlays OBJECT ${PE_OVERLAY_LIST})
target_sources(game_overlays PRIVATE src/port/area_updates.c)
target_sources(game_overlays PRIVATE src/port/encounter_spots.c)
target_include_directories(game_overlays PUBLIC include include/decomp
    ${CMAKE_CURRENT_SOURCE_DIR}/build/include)
target_compile_definitions(game_overlays PUBLIC __psyz SKIP_ASM)
target_compile_options(game_overlays PRIVATE -w -Wno-incompatible-function-pointer-types -g -fno-omit-frame-pointer -include port/gpu_len.h)
target_link_libraries(game_overlays PUBLIC psyz)

# src/port/asm_data.c holds game tables converted from the user's disc by tools/port/regen_stubs.sh; it is never
# committed, so a fresh checkout starts with an empty one.
if(NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/src/port/asm_data.c)
    file(WRITE ${CMAKE_CURRENT_SOURCE_DIR}/src/port/asm_data.c "")
endif()
add_executable(parasite-eve-ii-pc src/port/main.c src/port/psyq_host.c src/port/fixed_log.c src/port/pad_trace.c src/port/lzss.c src/port/tmd_dispatch.c src/port/tmd_prim.c src/port/tmd_ops.c src/port/mdec_vlc.c src/port/tmd_source.c src/port/tmd_layout.c src/port/cap_asset.c src/port/cap_resource.c src/port/disc_assets.c src/port/asset_loader.c src/port/asset_parts_table.c src/port/asm_data.c src/port/globals.c src/port/unresolved_stubs.c $<TARGET_OBJECTS:game_main>
    $<TARGET_OBJECTS:game_overlays>)
target_include_directories(parasite-eve-ii-pc PRIVATE include include/decomp src/main)
target_compile_definitions(parasite-eve-ii-pc PRIVATE __psyz SKIP_ASM)
target_link_libraries(parasite-eve-ii-pc PRIVATE psyz)
target_sources(parasite-eve-ii-pc PRIVATE src/port/spu_voice_attributes.c)

# Host test for the GTE compatibility macros: cmake --build build-port --target gte_compat_test
add_executable(gte_compat_test EXCLUDE_FROM_ALL tests/gte_compat_test.c)
target_include_directories(gte_compat_test PRIVATE include include/decomp)
target_compile_definitions(gte_compat_test PRIVATE __psyz SKIP_ASM)
target_link_libraries(gte_compat_test PRIVATE psyz)

# Development tool: reads one package straight from a disc image (src/port/disc_assets.c).
add_executable(pe2_discread EXCLUDE_FROM_ALL tools/port/discread.c src/port/disc_assets.c)
target_include_directories(pe2_discread PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(lzss_test EXCLUDE_FROM_ALL tests/lzss_test.c src/port/lzss.c)
target_include_directories(lzss_test PRIVATE include include/decomp src/main)
target_compile_definitions(lzss_test PRIVATE __psyz SKIP_ASM)
target_link_libraries(lzss_test PRIVATE psyz)

add_executable(tmd_model_test EXCLUDE_FROM_ALL tests/tmd_model_test.c src/port/tmd_dispatch.c)
target_include_directories(tmd_model_test PRIVATE include include/decomp src/main)
target_compile_definitions(tmd_model_test PRIVATE __psyz SKIP_ASM)
target_link_libraries(tmd_model_test PRIVATE psyz)

add_executable(tmd_prim_test EXCLUDE_FROM_ALL tests/tmd_prim_test.c src/port/tmd_prim.c src/port/tmd_dispatch.c)
target_include_directories(tmd_prim_test PRIVATE include include/decomp src/main)
target_compile_definitions(tmd_prim_test PRIVATE __psyz SKIP_ASM)
target_link_libraries(tmd_prim_test PRIVATE psyz)

add_executable(tmd_ops_test EXCLUDE_FROM_ALL tests/tmd_ops_test.c src/port/tmd_ops.c src/port/tmd_dispatch.c)
target_include_directories(tmd_ops_test PRIVATE include include/decomp src/main)
target_compile_definitions(tmd_ops_test PRIVATE __psyz SKIP_ASM)
target_link_libraries(tmd_ops_test PRIVATE psyz)

# Variant units: a package compiled from another package's shared source with its own -D parameters.
# Each is a separate object library so the parameters stay per package (see docs/PORT_PLAN.md).
function(pe_overlay_variant pkg unit src defs hdr)
    string(REPLACE "/" "__" tgt "pe_var_${unit}")
    if(NOT TARGET ${tgt})
        add_library(${tgt} OBJECT EXCLUDE_FROM_ALL ${CMAKE_CURRENT_SOURCE_DIR}/${src})
        target_include_directories(${tgt} PRIVATE include include/decomp build/include)
        target_compile_definitions(${tgt} PRIVATE __psyz SKIP_ASM ${defs})
        target_compile_options(${tgt} PRIVATE -w -Wno-incompatible-function-pointer-types -Wno-return-mismatch)
        target_link_libraries(${tgt} PRIVATE psyz)
        if(hdr)
            target_compile_options(${tgt} PRIVATE -include ${CMAKE_CURRENT_SOURCE_DIR}/${hdr})
        endif()
        set_property(GLOBAL APPEND PROPERTY PE_VARIANT_TARGETS ${tgt})
    endif()
endfunction()
include(cmake/overlay_variants.cmake)
# The P08 bank is also the unarmed Aya bank selected after returning the
# shooting-gallery loadout. Reuse its manifest-specific build parameters.
if(NOT PE_ALL_OVERLAYS)
    target_compile_options(pe_var_p08__p08 PRIVATE -g -fno-omit-frame-pointer -include port/gpu_len.h)
    # Both console packages export their own copy of the authored idle clip.
    # Keep P08's bank bound to its copy when both overlays are resident.
    target_compile_definitions(pe_var_p08__p08 PRIVATE gAyaIdleClip=gP08AyaIdleClip)
    target_sources(parasite-eve-ii-pc PRIVATE $<TARGET_OBJECTS:pe_var_p08__p08>)
endif()
if(NOT PE_ALL_OVERLAYS)
    target_compile_options(pe_var_actor_101900__actor_01900 PRIVATE -g -fno-omit-frame-pointer "SHELL:-include port/gpu_len.h")
    target_compile_definitions(pe_var_actor_101900__actor_01900 PRIVATE PE_HOST_ALIAS_ACTOR301900)
    target_sources(parasite-eve-ii-pc PRIVATE $<TARGET_OBJECTS:pe_var_actor_101900__actor_01900>)
endif()
if(NOT PE_ALL_OVERLAYS)
    target_compile_options(pe_var_actor_101200__actor_01200 PRIVATE -g -fno-omit-frame-pointer "SHELL:-include port/gpu_len.h")
    target_sources(parasite-eve-ii-pc PRIVATE $<TARGET_OBJECTS:pe_var_actor_101200__actor_01200>)
endif()
if(NOT PE_ALL_OVERLAYS)
    # This manifest variant exports both gActor01100Tasks and its gActor301100Tasks alias.
    target_compile_options(pe_var_actor_301100__actor_01100 PRIVATE -g -fno-omit-frame-pointer "SHELL:-include port/gpu_len.h")
    target_compile_definitions(pe_var_actor_301100__actor_01100 PRIVATE PE_HOST_ALIAS_ACTOR101100)
    target_sources(parasite-eve-ii-pc PRIVATE $<TARGET_OBJECTS:pe_var_actor_301100__actor_01100>)
endif()
if(NOT PE_ALL_OVERLAYS)
    foreach(_fork_actor IN ITEMS
        actor_101600__actor_01600 actor_102000__actor_102000_text
        actor_102400__actor_02400 actor_102500__actor_02500
        actor_103700__actor_03700 actor_103800__actor_03800
        actor_104600__actor_04600 actor_105500__actor_05500
        actor_107000__actor_07000)
        target_compile_options(pe_var_${_fork_actor} PRIVATE -g -fno-omit-frame-pointer "SHELL:-include port/gpu_len.h")
        target_sources(parasite-eve-ii-pc PRIVATE $<TARGET_OBJECTS:pe_var_${_fork_actor}>)
    endforeach()
    target_compile_definitions(pe_var_actor_105500__actor_05500 PRIVATE PE_HOST_ALIAS_ACTOR205500)
    target_compile_definitions(pe_var_actor_102000__actor_102000_text PRIVATE
        gGolemScreamRecoverClip=gPawnGolemScreamRecoverClip
        gGolemPawnRookImpactSound=gPawnGolemImpactSound
        gGolemBuildupClip=gPawnGolemBuildupClip
        gGolemRecoilBehindClip=gPawnGolemRecoilBehindClip
        gGolemStaggerClip=gPawnGolemStaggerClip
        gGolemIdleClip=gPawnGolemIdleClip
        gGolemWalkClip=gPawnGolemWalkClip
        gGolemRecoilFrontClip=gPawnGolemRecoilFrontClip)
endif()
get_property(_pe_vars GLOBAL PROPERTY PE_VARIANT_TARGETS)
add_custom_target(overlay_variants DEPENDS ${_pe_vars})

add_executable(tmd_source_test EXCLUDE_FROM_ALL tests/tmd_source_test.c src/port/tmd_source.c)
target_include_directories(tmd_source_test PRIVATE include include/decomp)
target_compile_definitions(tmd_source_test PRIVATE __psyz SKIP_ASM)
target_link_libraries(tmd_source_test PRIVATE psyz)

add_executable(image_workspace_test EXCLUDE_FROM_ALL tests/image_workspace_test.c)
target_include_directories(image_workspace_test PRIVATE include include/decomp)
target_compile_definitions(image_workspace_test PRIVATE __psyz SKIP_ASM)
target_link_libraries(image_workspace_test PRIVATE psyz)

add_executable(tmd_layout_test EXCLUDE_FROM_ALL tests/tmd_layout_test.c src/port/tmd_layout.c)
target_include_directories(tmd_layout_test PRIVATE include include/decomp)
target_compile_definitions(tmd_layout_test PRIVATE __psyz SKIP_ASM)
target_link_libraries(tmd_layout_test PRIVATE psyz)

add_executable(tmd_layout_assets_test EXCLUDE_FROM_ALL tests/tmd_layout_assets_test.c src/port/tmd_layout.c)
target_include_directories(tmd_layout_assets_test PRIVATE include include/decomp build/include)
target_compile_definitions(tmd_layout_assets_test PRIVATE __psyz SKIP_ASM)
target_link_libraries(tmd_layout_assets_test PRIVATE psyz)

add_executable(cap_asset_test EXCLUDE_FROM_ALL tests/cap_asset_test.c src/port/cap_asset.c)
target_include_directories(cap_asset_test PRIVATE include include/decomp)
target_compile_definitions(cap_asset_test PRIVATE __psyz SKIP_ASM)
target_link_libraries(cap_asset_test PRIVATE psyz)

add_executable(cap_resource_test EXCLUDE_FROM_ALL tests/cap_resource_test.c src/port/cap_asset.c src/port/cap_resource.c)
target_include_directories(cap_resource_test PRIVATE include include/decomp)
target_compile_definitions(cap_resource_test PRIVATE __psyz SKIP_ASM)
target_link_libraries(cap_resource_test PRIVATE psyz)

add_executable(task_message_test EXCLUDE_FROM_ALL tests/task_message_test.c src/gameplay/task_message.c)
target_include_directories(task_message_test PRIVATE include include/decomp)
target_compile_definitions(task_message_test PRIVATE __psyz SKIP_ASM)
target_link_libraries(task_message_test PRIVATE psyz)

add_executable(cd_pump_test EXCLUDE_FROM_ALL tests/cd_pump_test.c)
target_include_directories(cd_pump_test PRIVATE include include/decomp)
target_compile_definitions(cd_pump_test PRIVATE __psyz SKIP_ASM)
target_link_libraries(cd_pump_test PRIVATE psyz)

add_executable(sprite_packet_test EXCLUDE_FROM_ALL tests/sprite_packet_test.c)
target_include_directories(sprite_packet_test PRIVATE include include/decomp)
target_compile_definitions(sprite_packet_test PRIVATE __psyz SKIP_ASM)
target_link_libraries(sprite_packet_test PRIVATE psyz)

add_executable(text_palette_test EXCLUDE_FROM_ALL tests/text_palette_test.c src/main/text_palette.c)
target_include_directories(text_palette_test PRIVATE include include/decomp build/include)
target_compile_definitions(text_palette_test PRIVATE __psyz SKIP_ASM)
target_link_libraries(text_palette_test PRIVATE psyz)

add_executable(ordering_table_test EXCLUDE_FROM_ALL tests/ordering_table_test.c)
target_compile_definitions(ordering_table_test PRIVATE __psyz SKIP_ASM)
target_link_libraries(ordering_table_test PRIVATE psyz)

add_executable(scene_broadcast_test EXCLUDE_FROM_ALL tests/scene_broadcast_test.c src/gameplay/task_message.c)
add_executable(spu_key_status_test EXCLUDE_FROM_ALL tests/spu_key_status_test.c)
add_executable(spu_voice_attributes_test EXCLUDE_FROM_ALL tests/spu_voice_attributes_test.c src/port/spu_voice_attributes.c)
target_compile_definitions(spu_voice_attributes_test PRIVATE __psyz)
target_link_libraries(spu_voice_attributes_test PRIVATE psyz)
add_executable(sound_slot_start_test EXCLUDE_FROM_ALL tests/sound_slot_start_test.c)
target_include_directories(sound_slot_start_test PRIVATE include include/decomp src/main)
target_compile_definitions(sound_slot_start_test PRIVATE __psyz SKIP_ASM)
target_link_libraries(sound_slot_start_test PRIVATE psyz)
if(APPLE)
    target_link_options(sound_slot_start_test PRIVATE -Wl,-dead_strip)
else()
    target_link_options(sound_slot_start_test PRIVATE -Wl,--gc-sections)
endif()
target_compile_definitions(spu_key_status_test PRIVATE __psyz)
target_link_libraries(spu_key_status_test PRIVATE psyz)

target_include_directories(scene_broadcast_test PRIVATE include include/decomp build/include src/main)
target_compile_definitions(scene_broadcast_test PRIVATE __psyz SKIP_ASM)
target_compile_options(scene_broadcast_test PRIVATE -w -Wno-incompatible-function-pointer-types)
target_link_libraries(scene_broadcast_test PRIVATE psyz)
if(APPLE)
    target_link_options(scene_broadcast_test PRIVATE -Wl,-dead_strip)
else()
    target_link_options(scene_broadcast_test PRIVATE -Wl,--gc-sections)
endif()

add_executable(observatory_scene_lifecycle_test EXCLUDE_FROM_ALL tests/observatory_scene_lifecycle_test.c)
target_include_directories(observatory_scene_lifecycle_test PRIVATE include include/decomp build/include)
target_compile_definitions(observatory_scene_lifecycle_test PRIVATE __psyz SKIP_ASM)
target_compile_options(observatory_scene_lifecycle_test PRIVATE -Wno-incompatible-function-pointer-types)
target_link_libraries(observatory_scene_lifecycle_test PRIVATE psyz)
if(APPLE)
    target_link_options(observatory_scene_lifecycle_test PRIVATE -Wl,-dead_strip)
else()
    target_link_options(observatory_scene_lifecycle_test PRIVATE -Wl,--gc-sections)
endif()

add_executable(gpu_tpage_test EXCLUDE_FROM_ALL tests/gpu_tpage_test.c)
target_include_directories(gpu_tpage_test PRIVATE include include/decomp)
target_compile_definitions(gpu_tpage_test PRIVATE __psyz SKIP_ASM)
target_link_libraries(gpu_tpage_test PRIVATE psyz)

add_executable(pad_trace_test EXCLUDE_FROM_ALL tests/pad_trace_test.c src/port/pad_trace.c)
target_include_directories(pad_trace_test PRIVATE include)

add_executable(player_target_test EXCLUDE_FROM_ALL tests/player_target_test.c src/gameplay/player_target.c)
target_include_directories(player_target_test PRIVATE include include/decomp)
target_compile_definitions(player_target_test PRIVATE __psyz SKIP_ASM)
target_link_libraries(player_target_test PRIVATE psyz)

add_executable(action_trigger_test EXCLUDE_FROM_ALL tests/action_trigger_test.c src/gameplay/collision_grid.c src/gameplay/object_lists.c)
target_include_directories(action_trigger_test PRIVATE include include/decomp build/include)
target_compile_definitions(action_trigger_test PRIVATE __psyz SKIP_ASM)
target_link_libraries(action_trigger_test PRIVATE psyz)
if(APPLE)
    target_link_options(action_trigger_test PRIVATE -Wl,-dead_strip)
else()
    target_link_options(action_trigger_test PRIVATE -Wl,--gc-sections)
endif()

add_executable(pair_contact_test EXCLUDE_FROM_ALL tests/pair_contact_test.c src/gameplay/collision_grid.c src/gameplay/object_lists.c)
target_include_directories(pair_contact_test PRIVATE include include/decomp)
target_compile_definitions(pair_contact_test PRIVATE __psyz SKIP_ASM)
target_link_libraries(pair_contact_test PRIVATE psyz)
if(APPLE)
    target_link_options(pair_contact_test PRIVATE -Wl,-dead_strip)
else()
    target_link_options(pair_contact_test PRIVATE -Wl,--gc-sections)
endif()

add_executable(scene_sector_test EXCLUDE_FROM_ALL tests/scene_sector_test.c)
target_include_directories(scene_sector_test PRIVATE include include/decomp)
target_compile_definitions(scene_sector_test PRIVATE __psyz SKIP_ASM)
target_link_libraries(scene_sector_test PRIVATE psyz)
if(APPLE)
    target_link_options(scene_sector_test PRIVATE -Wl,-dead_strip)
else()
    target_link_options(scene_sector_test PRIVATE -Wl,--gc-sections)
endif()

add_executable(area_resource_test EXCLUDE_FROM_ALL tests/area_resource_test.c src/gameplay/area_cd.c)
target_include_directories(area_resource_test PRIVATE include include/decomp)
target_compile_definitions(area_resource_test PRIVATE __psyz SKIP_ASM)
target_link_libraries(area_resource_test PRIVATE psyz)

add_executable(item_prompt_lifecycle_test EXCLUDE_FROM_ALL tests/item_prompt_lifecycle_test.c src/gameplay/item_notice.c)
target_include_directories(item_prompt_lifecycle_test PRIVATE include include/decomp)
target_compile_definitions(item_prompt_lifecycle_test PRIVATE __psyz SKIP_ASM)
target_link_libraries(item_prompt_lifecycle_test PRIVATE psyz)

add_executable(caption_packet_test EXCLUDE_FROM_ALL tests/caption_packet_test.c)
target_include_directories(caption_packet_test PRIVATE include include/decomp)
target_compile_definitions(caption_packet_test PRIVATE __psyz SKIP_ASM)
target_link_libraries(caption_packet_test PRIVATE psyz)
if(APPLE)
    target_link_options(caption_packet_test PRIVATE -Wl,-dead_strip)
else()
    target_link_options(caption_packet_test PRIVATE -Wl,--gc-sections)
endif()

add_executable(game_over_image_test EXCLUDE_FROM_ALL tests/game_over_image_test.c)
target_include_directories(game_over_image_test PRIVATE include include/decomp)
target_compile_definitions(game_over_image_test PRIVATE __psyz SKIP_ASM)
target_link_libraries(game_over_image_test PRIVATE psyz)
if(APPLE)
    target_link_options(game_over_image_test PRIVATE -Wl,-dead_strip)
else()
    target_link_options(game_over_image_test PRIVATE -Wl,--gc-sections)
endif()

add_executable(fountain_trigger_test EXCLUDE_FROM_ALL tests/fountain_trigger_test.c src/gameplay/object_lists.c)
target_include_directories(fountain_trigger_test PRIVATE include include/decomp build/include)
target_compile_definitions(fountain_trigger_test PRIVATE __psyz SKIP_ASM)
target_link_libraries(fountain_trigger_test PRIVATE psyz)
if(APPLE)
    target_link_options(fountain_trigger_test PRIVATE -Wl,-dead_strip)
else()
    target_link_options(fountain_trigger_test PRIVATE -Wl,--gc-sections)
endif()

add_executable(fixed_log_test EXCLUDE_FROM_ALL tests/fixed_log_test.c src/port/fixed_log.c src/gameplay/object_lists.c)
target_include_directories(fixed_log_test PRIVATE include include/decomp)
target_compile_definitions(fixed_log_test PRIVATE __psyz SKIP_ASM)
target_link_libraries(fixed_log_test PRIVATE psyz)
if(APPLE)
    target_link_options(fixed_log_test PRIVATE -Wl,-dead_strip)
else()
    target_link_options(fixed_log_test PRIVATE -Wl,--gc-sections)
endif()

add_executable(rupert_eyes_test EXCLUDE_FROM_ALL tests/rupert_eyes_test.c)
target_include_directories(rupert_eyes_test PRIVATE include include/decomp build/include)
target_compile_definitions(rupert_eyes_test PRIVATE __psyz SKIP_ASM)
target_link_libraries(rupert_eyes_test PRIVATE psyz)
if(APPLE)
    target_link_options(rupert_eyes_test PRIVATE -Wl,-dead_strip)
else()
    target_link_options(rupert_eyes_test PRIVATE -Wl,--gc-sections)
endif()

add_executable(cap_room_command_test EXCLUDE_FROM_ALL tests/cap_room_command_test.c src/gameplay/cap_commands.c src/port/cap_asset.c)
target_include_directories(cap_room_command_test PRIVATE include include/decomp)
target_compile_definitions(cap_room_command_test PRIVATE __psyz SKIP_ASM)
target_link_libraries(cap_room_command_test PRIVATE psyz)
if(APPLE)
    target_link_options(cap_room_command_test PRIVATE -Wl,-dead_strip)
else()
    target_link_options(cap_room_command_test PRIVATE -Wl,--gc-sections)
endif()
