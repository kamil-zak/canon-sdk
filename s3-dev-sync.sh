#!/bin/bash

local_dir="/Users/kamil/Work/picsane/tests/canon-sdk"
remote_dir="~/"
ssh_key="/Users/kamil/Work/keys/BaseUS.pem"
ssh_user="admin"
ssh_host="54.234.29.48"

rsync -avz --exclude='.git/' --exclude='sync.sh' -e "ssh -i ${ssh_key}" "${local_dir}" "${ssh_user}@${ssh_host}:${remote_dir}"