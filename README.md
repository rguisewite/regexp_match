Miva Merchant Regular Expression Match
============

**Note: Before you begin, you will need to set up the regexp library (see the rguisewite/regexp project for details)**

This library will allow you to search a given string for a regular expression and will return an object list of matched data. There are currently two functions available for use in this library:

```
	regexp_match( expression, source, flags, start )
	regexp_match_var( expression, source var, flags, start )
```

The functions are identical except for their use of the variable reference "source". The following is a breakdown of the function and its parameters, along with return data:

```
	regexp_match( expression, source, flags, start )
		expression: Regular Expression used to search. Follows JavaScript RegExp rules
		source: Source text used to find matches (can be text or variable reference depending on used function. See above)
		flags: If specified, can have any combination of the following values:
			'g': Global match
			'i': Ignore case
			'm': Multi-line - Treat beginning/end characters (^ and $) as working over multiple lines
		start: First index looked at when searching for matches
	
	Return value:
		matches: An array of objects containing data for the matches (index, matched string, etc).
			The following is an example of returns "matches":
				regexp_match( 'erchant$', 'Miva Merchant', '', 1 )

				returns:
					l.matches[ 1 ]:index = 7
					l.matches[ 1 ]:last_index = 13
					l.matches[ 1 ]:match = 'erchant'

					aka

					[
						{
							index: 7,
							last_index: 13,
							match: 'erchant'
						}
					]
```
