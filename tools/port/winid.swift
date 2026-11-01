import CoreGraphics
import Foundation
let l = CGWindowListCopyWindowInfo([.optionAll], kCGNullWindowID) as! [[String: Any]]
for w in l {
  guard let o = w[kCGWindowOwnerName as String] as? String, o.contains("parasite-eve-ii"),
        (w[kCGWindowLayer as String] as? Int) == 0,
        let b = w[kCGWindowBounds as String] as? [String: Any], (b["Height"] as? Double ?? 0) > 100 else { continue }
  print(w[kCGWindowNumber as String]!); break }
