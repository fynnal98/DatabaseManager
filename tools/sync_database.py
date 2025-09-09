import shutil
from pathlib import Path

def sync_database(project_dir: Path):
    db_src = project_dir / "extern/Database/database.json"
    db_dst = project_dir / "data/database.json"

    if not db_src.exists():
        print(f"⚠️  WARNUNG: {db_src} existiert nicht, keine Database synchronisiert!")
        return

    print(f"🔄 Sync Database: {db_src} -> {db_dst}")
    db_dst.parent.mkdir(parents=True, exist_ok=True)
    shutil.copy(db_src, db_dst)

def before_uploadfs(source, target, env):
    project_dir = Path(env['PROJECT_DIR'])
    sync_database(project_dir)

def before_build(source, target, env):
    project_dir = Path(env['PROJECT_DIR'])
    sync_database(project_dir)

if __name__ == "__main__":
    # manuell ausgeführt → gehe von tools/ 3 Ebenen hoch bis AIRLAB_Flightcontroller/
    project_dir = Path(__file__).resolve().parents[3]
    sync_database(project_dir)
