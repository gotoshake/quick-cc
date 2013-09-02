-- test graph: if G[u][v] == 0, there is no edge between u and v
function BFS(graph, mapWidth, mapHeight, startx, starty, ability)
	local visited = {}
	local queue = {}
	local n = 0
	visited[starty*mapWidth + startx] = true
	queue = {starty*mapWidth + startx}

	while #queue ~= 0 and n < ability do
		n = n+1
		local tempQueue = queue
		queue = {}
		for k,u in pairs(tempQueue) do
			local x = u%mapWidth
			local y = (u-x)/mapWidth

			if x-1>=0 and not visited[u-1] then
				table.insert(queue, u-1)
				visited[u-1] = true
			end

			if x+1<mapWidth and not visited[u+1] then
				table.insert(queue, u+1)
				visited[u+1] = true
			end

			if y-1>=0 and not visited[u-mapWidth] then
				table.insert(queue, u-mapWidth)
				visited[u-mapWidth] = true
			end

			if y+1<mapHeight and not visited[u+mapWidth]then
				table.insert(queue, u+mapWidth)
				visited[u+mapWidth] = true
			end
		end
	end

	return visited
end

local extract_min = function(opens, paths)
	local m = math.huge
	local i = 0
	for k, v in pairs(opens) do
		if paths[k] < m then
			m = paths[k]
			i = k
		end
	end
	opens[i] = nil -- remove i
	return i
end

function dijkstra (graph, mapWidth, mapHeight, startx, starty, ability)
	local paths = {}
	local previous = {}
	local closes = {}
	local opens = {}

	local alls = BFS(graph, mapWidth, mapHeight, startx, starty, ability)
	for k,v in pairs(alls) do paths[k] = math.huge end

	opens = alls
	paths[starty*mapWidth+startx] = 0

	for n = 0, #alls-1 do
		local u = extract_min(opens, paths)
		table.insert(closes, u)
		
		for k, v in pairs({u-1, u+1, u-mapWidth, u+mapWidth}) do
			if alls[v] and graph[v] > 0 and paths[v] > paths[u] + graph[v] then -- relax
				paths[v] = paths[u] + graph[v]
				previous[v] = u
			end
		end
	end
	return paths, previous
end

function path (p, start)
	local i = start
	local t = { i }
	while p[i] do
		table.insert(t, 1, p[i])
		i = p[i]
	end
	return t
end

G = {}
local mapWidth = 4
local mapHeight = 4
for v = 0, mapWidth*mapHeight-1 do G[v] = 1 end

paths,previous = dijkstra(G, mapWidth, mapHeight, 2, 1, 2)
for i,j in pairs(paths) do
	print(i, j, table.concat(path(previous, i), ' -> '))
end
