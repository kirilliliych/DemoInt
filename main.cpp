#include "demoint.hpp"


const size_t ARR_TO_SORT_SIZE = 12;


// DemoInt demo_selection_sort_get_smallest_elem_index(DemoInt *subarray, DemoInt cur_index, DemoInt subarray_size)
// {
//     assert(subarray != nullptr);
    
//     if (subarray_size <= 1)
//     {
//         return cur_index;
//     }

//     DemoInt temp_res = demo_selection_sort_get_smallest_elem_index(subarray + 1, cur_index + 1, subarray_size - 1);
//     DEMO_INT_COPY_CTOR(subsubarray_result, temp_res);

//     return subsubarray_result > *subarray ? *subarray : subsubarray_result; 
// }

// void demo_selection_sort(DemoInt *array, DemoInt *result, DemoInt cur_index, DemoInt array_size)
// {
//     assert(array  != nullptr);
//     assert(result != nullptr);

//     DemoInt temp_res = demo_selection_sort_get_smallest_elem_index(array, 0, array_size);
//     DEMO_INT_COPY_CTOR(index_with_smallest_elem, temp_res);

//     result[(int) cur_index] = index_with_smallest_elem == 0 ? *array : *(array + (int) index_with_smallest_elem);

//     if (array_size > 1)
//     {
//         demo_selection_sort(array + 1, result + 1, cur_index + 1, array_size - 1);
//     }
// }

// int main()
// {
//     DemoInt array_to_sort[ARR_TO_SORT_SIZE] = {10, 15, 1, -5, -228, -1337, 86, 100, 7, 14, -13, -1000};
//     DemoInt result[ARR_TO_SORT_SIZE] = {0};
//     demo_selection_sort(array_to_sort, result, 0, ARR_TO_SORT_SIZE);

//     return 0;
// }


int demo_selection_sort_get_smallest_elem_index(int *array, int cur_index, int array_size)
{
    assert(array != nullptr);
    
    std::cout << "demo_selection_sort_get_smallest..." << std::endl;
    std::cout << "cur_index: " << cur_index << ", array_size: " << array_size << std::endl; 
    if (array_size <= 1)
    {
        return cur_index;
    }

    int subarray_result = demo_selection_sort_get_smallest_elem_index(array, cur_index + 1, array_size - 1);

    return array[subarray_result] > *(array + cur_index) ? cur_index : subarray_result;      // here trouble with too much using variable
}

void demo_selection_sort(int *array, int *result, int cur_index, int array_size)
{
    assert(array  != nullptr);
    assert(result != nullptr);

    int index_with_smallest_elem = demo_selection_sort_get_smallest_elem_index(array, cur_index, array_size);
    result[cur_index] = array[index_with_smallest_elem];
    array[index_with_smallest_elem] = array[cur_index];

    if (array_size > 1)
    {
        demo_selection_sort(array, result, cur_index + 1, array_size - 1);
    }
}

int main()
{
    int array_to_sort[ARR_TO_SORT_SIZE] = {10, 15, 1, -5, -228, -1337, 86, 100, 7, 14, -13, -1000};
    int result[ARR_TO_SORT_SIZE] = {0};
    demo_selection_sort(array_to_sort, result, 0, ARR_TO_SORT_SIZE);
    for (int i = 0; i < ARR_TO_SORT_SIZE; ++i)
    {
        std::cout << result[i] << " ";
    }

    return 0;
}