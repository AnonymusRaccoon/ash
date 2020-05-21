#!/bin/sh

test_setup()
{
    if [ -f "$fictest".setup ]
    then
      . "$fictest".setup
    fi
}

test_unsetup()
{
    if [ -f "$fictest".unsetup ]
    then
	. "$fictest".unsetup
    fi
}

test_tcsh()
{
    test_setup
    /bin/cat "$fictest" | /bin/tcsh -f 2>tcsh.result >tcsh.result
    test_unsetup
}

test_42sh()
{
    test_setup
    /bin/cat "$fictest" | ./42sh 2> 42sh.result >42sh.result
    test_unsetup
}


fictest="$1"
echo "*** Launch $fictest ***"
rm -f tcsh.result 42sh.result
if [ ! -f "$fictest" ]
then
    echo "Test $fictest not found !" 1>&2
    exit 1
fi
if [ ! -f "42sh" ]
then
    echo "42sh not found !" 1>&2
    exit 1
fi
if [ ! -f "/bin/tcsh" ]
then
    echo "tcsh not found !" 1>&2
    exit 1
fi
(test_tcsh "$fictest")
(test_42sh "$fictest")
diff 42sh.result tcsh.result >/dev/null 2>/dev/null
if [ $? -eq 0 ]
then
    echo "  => OK"
    exit 0
else
    echo "  => FAILED"
    exit 1
fi
