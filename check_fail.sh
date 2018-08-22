./fail
# If the return code of the fail executable is a failure, then return success and vice versa.
RET=$?
if [ $RET -ne 0 ]; then
    exit 0
else
    echo "Tests were expected to output failing return code"
    exit 1
fi

