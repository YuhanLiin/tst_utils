./fail
# If the return code of the fail executable is a failure, then return success and vice versa.
if [ $? -ne 0 ]; then
    exit 0
else
    exit 1
fi

