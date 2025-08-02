#!/usr/bin/env bash
set -e
SCRIPT_DIR="$(dirname "$(readlink -f "$0")")"
exec matlab -nosplash -nodesktop -r "\
  addpath('$SCRIPT_DIR'); \
  disp('*** MATLAB: arrancou ur5e_publish_joints ***'); \
  try, ur5e_publish_joints; catch ME, disp(getReport(ME)); end"
