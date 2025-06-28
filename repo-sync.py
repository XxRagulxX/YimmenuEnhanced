import subprocess
import os
import sys

# Configuration
UPSTREAM_REMOTE = "upstream"
UPSTREAM_BRANCH = "enhanced"
LASTCOMMIT_FILE = ".lastcommit"
SKIP_MESSAGE = "Merge branch 'enhanced' of https://github.com/YimMenu/YimMenuV2 into enhanced"

def run_git(args, capture_output=True):
    result = subprocess.run(
        ["git"] + args,
        capture_output=capture_output,
        text=True,
        check=True
    )
    if capture_output:
        return result.stdout.strip()
    return None

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
    """
    Get new commits from upstream/enhanced since last_commit,
    following the first-parent path (linear history).
    """
    if last_commit:
        rev_range = f"{last_commit}..{UPSTREAM_REMOTE}/{UPSTREAM_BRANCH}"
        log = run_git([
            "rev-list", "--reverse", "--ancestry-path", "--first-parent", rev_range
        ])
    else:
        log = run_git([
            "rev-list", "--reverse", "--first-parent", f"{UPSTREAM_REMOTE}/{UPSTREAM_BRANCH}"
        ])
    commits = log.splitlines()
    return commits

def get_commit_message(commit_sha):
    return run_git(["show", "-s", "--format=%B", commit_sha])

def main():
    fetch_upstream()
    last_commit = get_last_commit()
    new_commits = get_new_commits(last_commit)
    if not new_commits:
        print("No new commits to cherry-pick.")
        return

    print(f"Found {len(new_commits)} new commits to process.")
    skipped_count = 0

    for commit in new_commits:
        commit_msg = get_commit_message(commit)
        # Skip commits with the specific merge message
        if SKIP_MESSAGE in commit_msg:
            print(f"Skipping merge commit: {commit}")
            set_last_commit(commit)
            skipped_count += 1
            continue

        print(f"Cherry-picking {commit}...")
        try:
            run_git(["cherry-pick", "-x", commit], capture_output=False)
            set_last_commit(commit)
        except subprocess.CalledProcessError:
            print(f"Conflict or error during cherry-pick of {commit}. Resolve manually, then re-run the script.")
            sys.exit(1)

    print(f"\nSummary:")
    print(f"- Processed {len(new_commits)} commits")
    print(f"- Cherry-picked {len(new_commits) - skipped_count} commits")
    print(f"- Skipped {skipped_count} merge commits")
    print("Operation completed successfully.")

if __name__ == "__main__":
    main()