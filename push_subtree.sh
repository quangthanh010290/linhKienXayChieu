esp8266=$(git remote | grep "thanh_esp8266")
servo=$(git remote | grep "thanh_servo")
stm32=$(git remote | grep "thanh_stm32")

if  [ ! -z "$esp8266" ] ; then
	git subtree push --prefix=thanh_esp8266 thanh_esp8266 master
fi

if  [ ! -z "$servo" ] ; then
	git subtree push --prefix=thanh_servo thanh_servo master
fi


if  [ ! -z "$stm32" ] ; then
	git subtree push --prefix=thanh_stm32 thanh_stm32 master
fi


