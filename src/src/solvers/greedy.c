#include "ds_finder.h"

static t_ull find_best_candidate(t_graph *g, t_ull *curr_degrees)
{
    t_ull   best_node;
    t_ull   max_deg;
    t_ull   i;

    best_node = (t_ull)-1;
    max_deg = 0;
    i = 0;
    while (i < g->v_count)
    {
        if (g->actives[i] && curr_degrees[i] > max_deg)
        {
            max_deg = curr_degrees[i];
            best_node = i;
        }
        i++;
    }
    return (best_node);
}

static t_ull *init_degrees(t_graph *g)
{
    t_ull   *arr;
    t_ull   i;

    arr = malloc(sizeof(t_ull) * g->v_count);
    if (!arr)
        return (NULL);
    i = 0;
    while (i < g->v_count)
    {
        if (g->actives[i])
            arr[i] = g->nodes[i].degree;
        else
            arr[i] = 0;
        i++;
    }
    return (arr);
}

static void update_neighbors_score(t_graph *g, t_ull u, t_ull *curr_degrees)
{
    t_ull   i;
    t_ull   v;
    t_node  *node_u;

    node_u = &g->nodes[u];
    i = 0;
    while (i < node_u->degree)
    {
        v = node_u->neighbors[i];
        if (g->actives[v] && curr_degrees[v] > 0)
            curr_degrees[v]--;
		g->actives[v] = false;
        i++;
    }
}

void solve_greedy(t_graph *graph)
{
    t_ull   *curr_degrees;
    t_ull   best_node;

    if (!graph->solutions)
        graph->solutions = ft_calloc(graph->v_count, sizeof(bool));
    curr_degrees = init_degrees(graph);
    if (!curr_degrees)
        return ;
    while (1)
    {
        best_node = find_best_candidate(graph, curr_degrees);
        if (best_node == (t_ull)-1)
            break ;
        graph->solutions[best_node] = true;
        graph->len_solutions++;
        update_neighbors_score(graph, best_node, curr_degrees);
        curr_degrees[best_node] = 0;
    }
    free(curr_degrees);
}