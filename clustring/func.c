#include "cluster.h"

void unselected_tree_traversal(struct NODE *unselected_points, struct NODE **new_head, unsigned char center, int* min_pts, int *first_time, int *dynamic_raduis, struct NODE **potential_clusters)
{

    if(unselected_points == NULL)
        return;
    
    
    if(left!=NULL)
        unselected_tree_traversal(left, new_head, center, min_pts, first_time, dynamic_raduis, potential_clusters);
    
    if(right!=NULL)
        unselected_tree_traversal(right, new_head, center, min_pts, first_time, dynamic_raduis, potential_clusters);
}
