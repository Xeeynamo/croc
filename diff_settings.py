#!/usr/bin/env python3

def apply(config, args):
    config["arch"] = "mipsel"
    config['baseimg'] = f'CROC.EXE'
    config['myimg'] = f'build/croc.exe'
    config['mapfile'] = f'build/croc.map'
    config['source_directories'] = [f'src/croc', 'include', f'asm/croc']
