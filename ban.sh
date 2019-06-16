#!/bin/bash
./IP-List /var/log/nginx/proxy.log -nwl > UnknowList
./IP-List UnknowList -db
read -p "将以上IP加入黑名单？[Y/N]" answer
case $answer in
Y|y)
    for line in `cat UnknowList`
    do
        ipset add blacklist $line
    done
esac
exit 0
