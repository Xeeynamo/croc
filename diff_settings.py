#!/usr/bin/env python3

import os


def add_custom_arguments(parser):
    parser.add_argument(
        "--version",
        default="sled00038",
        dest="version",
        help="Decide what version of the game to use (list of builds in disks/README)",
    )
    parser.add_argument(
        "--overlay",
        default="croc",
        dest="overlay",
        help="Defines which overlay to use for the diff",
    )

def apply(config, args):
    version = args.version or os.getenv("VERSION") or "sled00038"
    name = args.overlay or "croc"
    config["arch"] = "mipsel"
    config['baseimg'] = f'disks/{version}/' + (f"/{name}.PRG").upper()
    config['myimg'] = f'build/' + (f"/{name}.exe").upper()
    config['mapfile'] = f'build/{name}.map'
    config['source_directories'] = [f'src/{name}', 'include', f'asm/{name}']
