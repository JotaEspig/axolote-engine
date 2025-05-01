import sys
import os


def get_version():
    if len(sys.argv) > 1:
        os.chdir(sys.argv[1])

    with open(".cz.toml", "r") as f:
        lines = f.readlines()
        for line in lines:
            if line.startswith("version = "):
                version = line.split("=")[1].strip().strip('"')
                return version


if __name__ == "__main__":
    print(get_version())
