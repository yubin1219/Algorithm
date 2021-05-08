def dfs(v):
  visited[v] = True
  for e in adj[v]:
    if not (visited[e]):
      dfs(e)
      
## 2-D
dx = [-1, 1, 0, 0]
dy = [0, 0, 1, -1]

def def2(x, y):
  visited[x][y] = True
  for i in range(4):
    nx, ny = x + dx[i], y + dy[i]
    if nx < 0 or nx >= n or ny < 0 or ny >= m:
      continue
    if not (visited[nx][ny]):
      dfs2(nx, ny)
