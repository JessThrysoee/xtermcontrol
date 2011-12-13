dnl XTC_PACKAGE_DATE
dnl make PACKAGE_DATE shell variable available with bootstrap date, e.g. "July 25, 2002"
AC_DEFUN([XTC_PACKAGE_DATE], 
[
   PACKAGE_DATE="esyscmd([date +'%B %d[,] %Y"'])
   AC_SUBST(PACKAGE_DATE)
])
