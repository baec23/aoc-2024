path starts 0 ends 9
only up/down/left/right

dp

find all 0s
find all 9s

for each 0
for each 9
set of visited
recurse to see if can get to 9
add+1 to curr0sum if got to end
add curr0sum to totalsum
return totalsum
