#!/usr/bin/env python

import os
import sys

BUILD_OPTS = {'--debug', '--release'}

USAGE = """
USAGE:
    build.py ({build_opts})
""".format(build_opts=' | '.join(BUILD_OPTS))

if __name__ == '__main__':
    args = sys.argv[1:]

    if len(args) != 1 or args[0] not in BUILD_OPTS:
        print(USAGE)
        exit(1)

    project_path = os.path.dirname(os.path.realpath(__file__))
    build_type = args[0][2:]
    build_path = os.path.join(project_path, 'cmake-build-{build_type}'.format(build_type=build_type))

    if not os.path.exists(build_path):
        os.makedirs(build_path)

    os.chdir(build_path)
    os.system('cmake -DCMAKE_BUILD_TYPE={build_type} ..'.format(build_type=build_type))
    os.system('make')
