echo "he'l"   #done
echo "he'l"'  #done
echo "'$PWD'" #done
echo $$       //err
echo $USER$   #done
// seg
cat << lim    #done

==== error ===

echo | #done
| grep #done

echo hds <|hds


invalid redirection    <<da #done
Unexpected token           ||  or |hdfj  or | #done
Unexpected token newlin  ed>> #done



============ WHY ???

$$PWD
$$
$USER$


==============
in bash :
	    echo $USER$ = aheddak$
		echo $$USER = 29166USER(first $ = id of process bash )
		echo $$     = 29166
eandi :
		echo $user$ = echo [EXPANDED VALUE]$
		echo $$user = echo $[EXPANDED VALUE]
		echo $$ 	= $$