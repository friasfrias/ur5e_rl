#!/usr/bin/env bash
set -e
SCRIPT_DIR="$(dirname "$(readlink -f "$0")")"
exec matlab -nosplash -nodesktop -r "\
  addpath('$SCRIPT_DIR'); \
  disp('*** MATLAB: arrancou pidControlNode ***'); \
  try, pidControlNode; catch ME, disp(getReport(ME)); end"