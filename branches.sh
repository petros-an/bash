x=`git for-each-ref --format='%(refname:short)' refs/heads | xargs echo`
y=$(git branch | awk '/^\* / { print $2 }')
z=`~/options/bin/options $y $x | tr -cd "[:print:]\n" `
git checkout $z

