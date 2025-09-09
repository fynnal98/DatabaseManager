#!/usr/bin/env python3
import json
from pathlib import Path

# Pfade
BASE_DIR = Path(__file__).resolve().parent.parent
DB_FILE = BASE_DIR / "../Database/database.json"
OUT_DIR = BASE_DIR / "generated"
OUT_FILE = OUT_DIR / "protocol_ids.h"

def main():
    # JSON laden
    with open(DB_FILE, "r") as f:
        db = json.load(f)

    params = db["protocol"]["parameters"]
    msgs = db["protocol"]["messages"]

    OUT_DIR.mkdir(parents=True, exist_ok=True)

    with open(OUT_FILE, "w") as out:
        out.write("#pragma once\n\n")
        out.write("// --- Auto-generated from database.json ---\n\n")

        # Parameter IDs
        out.write("// Parameter IDs\n")
        for path, info in params.items():
            name = path.upper().replace(".", "_")
            out.write(f"#define PARAM_{name:30} {info['id']}\n")
        out.write("\n")

        # Message IDs
        out.write("// Message IDs\n")
        for name, info in msgs.items():
            out.write(f"#define MSG_{name:30} {info['id']}\n")

    print(f"Generated {OUT_FILE}")

if __name__ == "__main__":
    main()
