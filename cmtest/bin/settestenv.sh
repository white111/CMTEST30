# settestenv.sh
################################################################################
#
# Module:      settestenv(.sh)
#
# Author:      Joe White
#
# Descr:       Script to change test bucket
#
# Version:    1.1 $Id: settestenv.sh,v 1.2 2008/02/20 23:05:33 joe Exp $
#
# Changes:
#
#
# Still ToDo:
#
#
#            Copyright (c) 2005-2008 Stoke. All rights reserved.
#
################################################################################
File=$HOME/tmp/bash.tmp
rm -f $File

settestenv $1

if [ -f $File ]; then
        . $File
fi

