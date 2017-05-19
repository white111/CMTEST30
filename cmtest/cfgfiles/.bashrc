#
# .bashrc   CM Test version 2
#

# remove /usr/games and /usr/X11R6/bin if you want
export PATH=/sbin:/bin:/usr/sbin:/usr/bin:/usr/local/sbin:/usr/local/bin:/usr/X11R6/bin:$HOME/bin

BLOCKSIZE=K;	export BLOCKSIZE
EDITOR=vi;   	export EDITOR
PAGER=more;  	export PAGER

# file permissions: rwxr-xr-x
umask	022

# set ENV to a file invoked each time sh is started for interactive use.
ENV=$HOME/.shrc; export ENV

# Netscreen Issue.
export FTP_PASSIVE_MODE=YES

# macro ()
# {
#	 Command here
# }

#Add your entry here
# -----------------------------------------

# CMTest aliases / variable declarations

. /usr/local/cmtest/.aliases
. /usr/local/cmtest/.cmtestrc


# -----------------------------------------
# for NFS resource don't remove
#
if [ "`uname`" = "Linux" ]; then
        if [ -e /auto/opt/etc/profile ]; then
                . /auto/opt/etc/profile
        fi
fi
