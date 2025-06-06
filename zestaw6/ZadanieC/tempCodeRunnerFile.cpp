    for (size_t i = 0; i < boost::num_vertices(g); ++i)
    {
        graph::vertex_descriptor v = boost::vertex(i, g);
        if (!visited[v])
        {
            dfs(g, v, visited, sortedVertices, counter);
        }
    }