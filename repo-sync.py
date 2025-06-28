import subprocess
import os
import sys

# Configuration
UPSTREAM_REMOTE = "upstream"
UPSTREAM_BRANCH = "enhanced"
LASTCOMMIT_FILE = ".lastcommit"

def run_git(args, capture_output=True):
    result = subprocess.run(
        ["git"] + args,
        capture_output=capture_output,
        text=True,
        check=True
    )
    return result.stdout.strip()

def get_last_commit():
    if os.path.exists(LASTCOMMIT_FILE):
        with open(LASTCOMMIT_FILE, "r") as f:
            return f.read().strip()
    return None

def set_last_commit(commit_sha):
    with open(LASTCOMMIT_FILE, "w") as f:
        f.write(commit_sha)

def fetch_upstream():
    print(f"Fetching from {UPSTREAM_REMOTE}...")
    run_git(["fetch", UPSTREAM_REMOTE])

def get_new_commits(last_commit):
    # List new commits in upstream branch since last_commit (oldest first)
    if last_commit:
        rev_range = f"{last_commit}..{UPSTREAM_REMOTE}/{UPSTREAM_BRANCH}"
    else:
        rev_range = f"{UPSTREAM_REMOTE}/{UPSTREAM_BRANCH}"
    log = run_git(["log", "--reverse", "--format=%H", rev_range])
    commits = log.splitlines()
    return commits

def main():
    fetch_upstream()
    last_commit = get_last_commit()
    new_commits = get_new_commits(last_commit)
    if not new_commits:
        print("No new commits to cherry-pick.")
        return

    print(f"Found {len(new_commits)} new commits to cherry-pick.")
    for commit in new_commits:
        print(f"Cherry-picking {commit}...")
        try:
            run_git(["cherry-pick", "-x", commit], capture_output=False)
            set_last_commit(commit)
        except subprocess.CalledProcessError:
            print(f"Conflict or error during cherry-pick of {commit}. Resolve manually, then re-run the script.")
            sys.exit(1)
    print("All new commits cherry-picked successfully.")

if __name__ == "__main__":
    main()