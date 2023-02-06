#include "demoint.hpp"


const size_t ARR_TO_SORT_SIZE = 12;


DemoInt demo_selection_sort_get_smallest_elem_index(DemoInt *array, DemoInt cur_index, DemoInt array_size)
{
    assert(array != nullptr);
     
    if (array_size <= 1)
    {
        return cur_index;
    }

    DemoInt subarray_result = demo_selection_sort_get_smallest_elem_index(array, cur_index + 1, array_size - 1);

    return array[subarray_result] > array[cur_index] ? cur_index : subarray_result;                            //
}

void demo_selection_sort(DemoInt *array, DemoInt *result, DemoInt cur_index, DemoInt array_size)
{
    assert(array  != nullptr);
    assert(result != nullptr);

    DemoInt index_with_smallest_elem = demo_selection_sort_get_smallest_elem_index(array, cur_index, array_size);
    result[cur_index] = array[index_with_smallest_elem];
    array[index_with_smallest_elem] = array[cur_index]; // 

    if (array_size > 1)
    {
        demo_selection_sort(array, result, cur_index + 1, array_size - 1);
    }
}

int main()
{
    DemoInt array_to_sort[ARR_TO_SORT_SIZE] = {10, 15, 1, -5, -228, -1337, 86, 100, 7, 14, -13, -1000};

    DemoInt result[ARR_TO_SORT_SIZE] = {0};
    demo_selection_sort(array_to_sort, result, 0, ARR_TO_SORT_SIZE);
    for (int i = 0; i < ARR_TO_SORT_SIZE; ++i)
    {
        std::cout << result[i] << " ";
    }

    return 0;
}