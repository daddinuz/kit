#!/usr/bin/env bash

set -e

echo "===[ Python ]=================>" > bench.log
x=1
while [ ${x} -le 5 ]; do
    (\time --portability --output=bench.log --append python3 -c "import os; import requests; response = requests.get('https://api.github.com/repos/daddinuz/kit/issues', headers={'Authorization': 'token {}'.format(os.environ['GITHUB_AUTH_TOKEN']), 'Accept': 'application/vnd.github.VERSION.raw+json', 'Content-Type': 'application/json', 'User-Agent': 'daddinuz/kit'}); print('headers: {}\nbody: {}\nstatus: {}'.format(response.headers, response.content, response.status_code))") > /dev/null
    echo >> bench.log
    x=$(( ${x} + 1 ))
done

echo "===[ C ]======================>" >> bench.log
x=1
while [ ${x} -le 5 ]; do
    (\time --portability --output=bench.log --append ./cmake-build-release/example_http) > /dev/null
    echo >> bench.log
    x=$(( ${x} + 1 ))
done
