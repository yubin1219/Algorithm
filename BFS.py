from collections import deque

def bfs(v):
  q = deque([v])
  while q:
    v = q.popleft()
    if not (visited[v]):
      visited[v]=True
      for e in adj[v]:
        if not visited[e]:
          q.append(e)

## Not use "import deque"
def BFS(v):
  q = []
  q.append(v)
  while q:
    v = q.pop(0)
    if not (visited[v]):
      visited[v]=True
      for e in adj[v]:
        if not visited[e]:
          q.append(e)
          
## 2-D          
dx = [1, -1, 0, 0]
dy = [0, 0, -1, 1]

def bfs2(i,j):
  q = deque([i,j])
  temp = [[i,j]]
  while q:
    x, y = q.popleft()
    for i in range(4):
      nx, ny = x + dx[i], y + dy[i]
      if 0 <= nx < n and 0 <= ny <n and visited[nx][ny] == 0:
        visited[nx][ny] = 1
        q.append([nx, ny])
        dist[nx][ny] = dist[x][y] + 1
