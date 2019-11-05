x=`git for-each-ref --format='%(refname:short)' refs/heads | xargs echo`
~/options/bin/options $cur_branch $x
