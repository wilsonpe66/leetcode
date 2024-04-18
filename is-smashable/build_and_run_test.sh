#/bin/bash

cd "$(dirname $0)"

BIN_FILE=./is-smashable
[ -f "${BIN_FILE}" ] && rm -vf "${BIN_FILE}"
g++ --std=c++17 -O3 -Wall is-smashable.cpp -o "${BIN_FILE}"
ls -la
${BIN_FILE} | tee output.log

strip "${BIN_FILE}"

ls -la "${BIN_FILE}"
