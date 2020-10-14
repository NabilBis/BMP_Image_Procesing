#include "cluster.h"

struct CLUSTER* new_cluster(unsigned char c, unsigned char r)
{
    struct CLUSTER* cluster = malloc(sizeof(struct NODE));
    
    cluster->center = c;
    cluster->radius = r;
    
    cluster->left = NULL;
    cluster->right = NULL;
    
    return cluster;
}

void add_cluster(struct CLUSTER *head, struct CLUSTER *new)
{
    new->left = NULL;
    new->right = NULL;
    
    if(head->left == NULL && head->center > new->center)
    {
        head->left = new;
        return;
    }
    
    if(head->right == NULL  && head->center <= new->center)
    {
        head->right = new;
        return;
    }
    
    return (head->center > new->center) ? add_cluster(head->left, new) : add_cluster(head->right, new);
}


void preOrder(struct NODE *head)
{
    if(head == NULL)
        return;
    
    printf(" %d \n", head->point);
    preOrder(head->leftNode);
    preOrder(head->rightNode);
}

//
void prer(struct CLUSTER *head)
{
    if(head == NULL)
        return;
    
    printf("Center = %d, Radius = %d\n", head->center, head->radius);
    
    prer(head->left);
    prer(head->right);
}

void add_new_node(struct NODE *head, struct NODE *new_node)
{
    new_node->leftNode = NULL;
    new_node->rightNode = NULL;

    if( head->leftNode == NULL && head->point > new_node->point)
    {
        head->leftNode = new_node;
        return;
    }
    
    if(head->rightNode == NULL  && head->point <= new_node->point)
    {
        head->rightNode = new_node;
        return;
    }
    
    return (head->point > new_node->point) ? add_new_node(head->leftNode, new_node) : add_new_node(head->rightNode, new_node);
}



void add_failed_potential_points(struct NODE *unselected_points, struct NODE *head, int arg)
{
    struct NODE *left = malloc(sizeof(struct NODE));
    struct NODE *right = malloc(sizeof(struct NODE));
    
    if(head == NULL)
        return;

    left = head->leftNode;
    right = head->rightNode;

    if(arg==2)
        add_new_node(unselected_points, head);
    
    
    add_failed_potential_points(unselected_points, left, 2);
    add_failed_potential_points(unselected_points, right, 2);
}





void build_initial_binary_tree(unsigned char* data, int dataSize, struct CLUSTER** clusters_head, struct NODE** noise_head, struct NODE **unselected_points, struct NODE* nodes)
{
    int dynamic_raduis;
    int distance;
    int is_head_set;
    int min_pt_counter;
    unsigned char center;
    unsigned char diff;
    double quotion;
    int *index = malloc(sizeof(int)*(__dbscan_min_points__-1));

    distance =  is_head_set = min_pt_counter = 0;
    dynamic_raduis = __dbscan_radius__;
    center = *(data+0);
    
    for(int i=0; i<dataSize; i++)
    {
        
        (nodes+i)->point = *(data+i);

        distance = manhattan(&center, data+i, 1);


        if(distance > dynamic_raduis)
        {
            if(!is_head_set)
            {
                *unselected_points = (nodes+i);
                is_head_set = i;
                continue;
            }
            
            add_new_node( (nodes+is_head_set), (nodes+i));
            continue;
        }
//        printf("Point added to cluster : %d\n",*(data+i));
        min_pt_counter++;

//        printf("Center = %d, dynamic_radius = %d, Point = %d, ", center, dynamic_raduis, *(data+i));
//        printf("Distance = %d\n", distance);
        if(min_pt_counter < __dbscan_min_points__)
        {
            *(index+min_pt_counter-1) = i;
        }
        
        //////// CENTER AND RADIUS UPDATE
        
        quotion = (double) ((__dbscan_radius__ - (dynamic_raduis - distance)) )/2;
        diff = quotion + (quotion*10)/5;
        
        if(distance <= dynamic_raduis && center < *(data+i))
            center += diff;
        
        if(distance <= dynamic_raduis && center > *(data+i))
            center -= diff;
        
        
        dynamic_raduis += diff;
        ////////////////////////////////////
    }
    
    if(min_pt_counter >= __dbscan_min_points__)
    {
        *clusters_head = new_cluster(center, dynamic_raduis);
        
    }
    else {
        
        for(int t=1; t<min_pt_counter; t++)
            add_new_node(*unselected_points, nodes + (*(index+t)) );
        
        nodes->leftNode = NULL;
        nodes->rightNode = NULL;
        *noise_head = nodes;
    }
}


//struct NODE *left;
//struct NODE *right;


void unselected_tree_traversal(struct NODE *unselected_points, struct NODE **new_head, unsigned char center, int* min_pts, int *first_time, int *dynamic_raduis, struct NODE **potential_clusters)
{
    int distance;
    struct NODE *left = malloc(sizeof(struct NODE));
    struct NODE *right = malloc(sizeof(struct NODE));
    int diff=0;
    double quotion;
   


    left = unselected_points->leftNode;
    right = unselected_points->rightNode;
    
    printf("From inside %d\n", *min_pts);
    if(unselected_points == NULL)
        return;
    
    if(!(*dynamic_raduis))
        *dynamic_raduis = __dbscan_radius__;

//    printf("Center %d, Dynamic %d\n", center, *dynamic_raduis);
    
    distance = manhattan(&unselected_points->point, &center, 1);
    
    if(distance > *dynamic_raduis)
    {
        if(!(*first_time))
        {
            unselected_points->leftNode = NULL;
            unselected_points->rightNode = NULL;
            
            *new_head = unselected_points;
        
            (*first_time)++;
            
        } else {
            add_new_node(*new_head, unselected_points);
        }
    }
    else {

        quotion = (double) ((__dbscan_radius__ - (*dynamic_raduis - distance)) )/2;
        diff = quotion + (quotion*10)/5;
        
        if(distance <= (*dynamic_raduis) && center < unselected_points->point)
        {
            center += diff;
        }

        if(distance <= (*dynamic_raduis) && center > unselected_points->point)
        {
            center -= diff;
        }
        
        
        *dynamic_raduis += diff;
        (*min_pts)++;

       
        if(*min_pts < __dbscan_min_points__)
        {
            if(*potential_clusters == NULL)
            {
                unselected_points->leftNode = NULL;
                unselected_points->rightNode = NULL;
                *potential_clusters = unselected_points;
            }
            else
            {
                add_new_node(*potential_clusters, unselected_points);
            }
            
        }
    }

    if(left!=NULL)
        unselected_tree_traversal(left, new_head, center, min_pts, first_time, dynamic_raduis, potential_clusters);
    
    if(right!=NULL)
        unselected_tree_traversal(right, new_head, center, min_pts, first_time, dynamic_raduis, potential_clusters);
}



//void fill_pixels_array(struct CLUSTER* head, unsigned char* array)
//{
//    int limit;
//    
//    
//    if(head == NULL)
//        return;
//    
//    limit = head->radius/2;
//    
//    
//    for(int u=0; u< limit; u++)
//    {
//        if((head->center - limit + u)>=0)
//            *(array + head->center - limit + u) = head->center;
//        
//        if((head->center + limit - u)<=255)
//            *(array + head->center + limit - u) = head->center;
//    }
//    
//    fill_pixels_array(head->left, array);
//    fill_pixels_array(head->right, array);
//}
//
//void fill_array_noise(struct NODE *head, unsigned char *array)
//{
//    if(head == NULL)
//        return;
//    
//    *(array + head->point) = head->point;
//    
//    fill_array_noise(head->leftNode, array);
//    fill_array_noise(head->rightNode, array);
//}



void dbscan(unsigned char* data, int dataSize, int radius, int min_points, unsigned char* pixel_array_256)
{
    
    struct NODE *nodes = malloc(sizeof(struct NODE)*dataSize);
    struct NODE **unselected_points = malloc(sizeof(struct NODE*));
    struct NODE **noise_tree = malloc(sizeof(struct NODE*));
    struct CLUSTER **cluster_tree = malloc(sizeof(struct CLUSTER*));
    struct NODE **recursive_head = malloc(sizeof(struct NODE*));
    struct NODE **potential_clusters = malloc(sizeof(struct NODE*));
    
    unsigned char center;
    int points;
    int first_time;
    int dynamic_raduis;
    
    __dbscan_radius__ = radius;
    __dbscan_min_points__ = min_points;

    *recursive_head = *unselected_points = *noise_tree = NULL;
    
    *cluster_tree = NULL;
    
    build_initial_binary_tree(data, dataSize, cluster_tree, noise_tree, unselected_points, nodes);

//    left = malloc(sizeof(struct NODE));
//    right = malloc(sizeof(struct NODE));
    
    while(*unselected_points != NULL && ((*unselected_points)->leftNode != NULL || (*unselected_points)->rightNode != NULL) )
    {
        printf("While %d\n", points);
        preOrder(*unselected_points);
        printf("\n");
        
        points = first_time = dynamic_raduis = 0;
        *potential_clusters = NULL;
        
        center = (*unselected_points)->point;


        unselected_tree_traversal(*unselected_points, recursive_head, center, &points, &first_time, &dynamic_raduis, potential_clusters);

        unselected_points = recursive_head;

        if(points >= __dbscan_min_points__)
        {
            printf("Yes------------------\n");
            if(*cluster_tree == NULL)
                *cluster_tree = new_cluster(center, dynamic_raduis);
            else
                add_cluster(*cluster_tree, new_cluster(center, dynamic_raduis));

        } else {

            printf("No------------\n");
            add_failed_potential_points(*unselected_points, *potential_clusters, 1);

            if(*noise_tree == NULL)
                *noise_tree = *potential_clusters;
            else
                add_new_node(*noise_tree, *potential_clusters);
            
        }
    }   /////////////// END WHILE

    ////
    prer(*cluster_tree);
    preOrder(*unselected_points);
//    printf("\n---------\n");
//    preOrder(*unselected_points);
//    printf("\n---------\n");
//    preOrder(*unselected_points);
//    printf("\n---------\n");
//    preOrder(*unselected_points);
//    printf("\n---------\n");
//    preOrder(*unselected_points);
//    printf("\n---------\n");
//    preOrder(*unselected_points);
//    printf("\n---------\n");
//    
//    fill_array_noise(*noise_tree, pixel_array_256);
//    fill_pixels_array(*cluster_tree, pixel_array_256);
}





//int main(int args, char** argv)
//{
//    
//    unsigned char *data = malloc(sizeof(char)*18);
//    unsigned char *pixel_array_256 = malloc(sizeof(char)*256);
//    
//    
//
////    *(data+0) = 12;
////    *(data+1) = 37;
////    *(data+2) = 84;
////    *(data+3) = 25;/////// 63
////    *(data+4) = 67;
////    *(data+5) = 5;
////    *(data+6) = 75;
////    *(data+7) = 30;
////    *(data+8) = 9;
////    *(data+9) = 13;
////    *(data+10) = 80;
////    *(data+11) = 69;
////    *(data+12) = 22;
////    *(data+13) = 70;
////    *(data+14) = 7;
////    *(data+15) = 27;
////    *(data+16) = 61;
////    *(data+17) = 1;
//    
////    *(data+0) = 1;
////    *(data+1) = 5;
////    *(data+2) = 7;
////    *(data+3) = 9;
////    *(data+4) = 12;
////    *(data+5) = 13;
////    *(data+6) = 22;
////    *(data+7) = 25;
////    *(data+8) = 27;
////    *(data+9) = 30;
////    *(data+10) = 37;
////    *(data+11) = 61;
////    *(data+12) = 67;
////    *(data+13) = 69;
////    *(data+14) = 70;
////    *(data+15) = 75;
////    *(data+16) = 80;
////    *(data+17) = 84;
//    
////    *(data+0) = 1;
////    *(data+1) = 1;
////    *(data+2) = 1;
////    *(data+3) = 2;
////    *(data+4) = 3;
////    *(data+5) = 3;
////    *(data+6) = 3;
////    *(data+7) = 4;
////    *(data+8) = 4;
////    *(data+9) = 12;
////    *(data+10) = 13;
////    *(data+11) = 14;
////    *(data+12) = 15;
////    *(data+13) = 16;
////    *(data+14) = 17;
////    *(data+15) = 18;
////    *(data+16) = 19;
////    *(data+17) = 20;
//
//    *(data+0) = 1;
//    *(data+1) = 2;//4;
//    *(data+2) = 3;//6;
//    *(data+3) = 4;//8;
//    *(data+4) = 11;
//    *(data+5) = 12;//15;
//    *(data+6) = 13;//18;
//    *(data+7) = 14;//20;
//    *(data+8) = 22;
//    *(data+9) = 23;//24;
//    *(data+10) = 24;//27;
//    *(data+11) = 25;//30;
//    *(data+12) = 32;
//    *(data+13) = 33;//35;
//    *(data+14) = 34;//37;
//    *(data+15) = 35;//40;
//    *(data+16) = 36;//42;
//    *(data+17) = 37;//45;
//    *(data+18) = 52;//37;
//    *(data+19) = 53;//40;
//    *(data+20) = 54;//42;
//    *(data+21) = 55;//45;
//    *(data+22) = 56;//42;
//    *(data+23) = 57;//45;
//    
//   dbscan(data, 12, 1, 4, pixel_array_256);
////    printf("+++++++ ++++++\n");
////    
////     for(int i=0; i<18; i++)
////       printf("%d ", *(data+i));
//    
//    printf("\nTu arriveras mon gars \n");
//    return EXIT_SUCCESS;
//}
