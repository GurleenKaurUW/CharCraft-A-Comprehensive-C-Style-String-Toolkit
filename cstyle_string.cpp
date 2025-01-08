#include <iostream>
#include "p_4_header.hpp"
#include <fstream>
#include <cassert>

std::size_t length( char const *a ){
    std::size_t len{0};
    while(a[len]!='\0') len++;
    return len;
}

int compare( char const *str1, char const *str2 ){

    //determine the smallest string's length
    std::size_t len{0};
    if(length(str1)<=length(str2))len = length(str1);
    else len = length(str2);

    //loop through each element and break if one letter comes before the other.

    for(std::size_t letter{0}; letter < len; letter++){
        if(str1[letter]<str2[letter])return -1;
        else if(str2[letter]<str1[letter]) return 1;
    }

    //words are the same up to this letter
    if(length(str1)<length(str2))return -1;
    else if(length(str1)>length(str2))return 1;

    //if you get here, both are the same length and the same word.
    return 0;
}

void assign( char *str1, char const *str2 ){
    std::size_t len = length(str2);

    for(std::size_t i{0}; i<len; i++){
        str1[i] = str2[i];

    }

    str1[len] = '\0';

    //printing
    // for(std::size_t i{0}; i<len; i++){
    //     std::cout<<str1[i];
    // }
    // std::cout<<std::endl;
    //end printing
}

unsigned int distance( char const *str1, char const *str2 ){
    if(compare(str1, str2)==0) {
        return 0;
    }
    else if(length(str1) == 0){ 
        return (unsigned int) length(str2);
    }
    else if(length(str2) == 0) {
        return (unsigned int) length(str1);
    }
    else if(str1[0] == str2[0]){
        return distance(str1 + 1, str2 + 1); //I can add one because they are pointers
    }
    return 1 + std::min(std::min(distance(str1 + 1, str2 + 1), distance(str1, str2 + 1)), distance(str1 + 1, str2));
    
}


std::size_t is_sorted( char *array[], std::size_t capacity ){
    for(std::size_t index{1}; index < capacity; index++){
        if(compare(array[index-1], array[index])==1)return index;
    }
    return capacity;
}

void insert( char *array[], std::size_t capacity ){

    char *last_entry = new char[length(array[capacity-1])];
    assign(last_entry, array[capacity-1]); //store the last entry
    //find where the entry belongs
    std::size_t index{0};
    while(compare(array[index], last_entry) < 0)index++;

    //shift everything after that spot by one place to the right
    for(std::size_t i = capacity - 1; i > index; i--) {
        assign(array[i], array[i-1]);
    }

    //store the last entry in the right place.
    assign(array[index], last_entry);

}

void insertion_sort( char *array[], std::size_t capacity ){
    for(std::size_t index{2}; index < capacity + 1; index ++){
        insert(array, index);
    }
}


std::size_t remove_duplicates( char *array[], std::size_t capacity ){
    std::size_t nbr_of_dup{0};
    for(std::size_t index{0}; index<capacity - nbr_of_dup; index++){
        bool is_duplicate = false;
        for(std::size_t k{0}; k<index; k++){
            if(compare(array[k], array[index]) == 0){
                is_duplicate = true;
                break;
            }
        }
        if(is_duplicate){
            nbr_of_dup ++;
            //duplicate --> shift everything to the left
            for(std::size_t k{index}; k<capacity - 1;k++){
                assign(array[k], array[k+1]);
            }
            index --;
        }
    }

    return capacity - nbr_of_dup; //return number of unique entries
}
std::size_t find( char *array[], std::size_t capacity, char const *str ){
    unsigned int min_distance = 0; 
    std::size_t min_dist_index;
    if(capacity == 0) return 0;
    if(capacity == 1) return distance(array[0], str);
    min_distance = distance(str, array[0]);
    for(std::size_t index{1}; index<capacity; index++){
        if(compare(array[index], str) == 0){
            return index;
        }
        if(distance(array[0], str)<min_distance){
            min_dist_index = index;
            min_distance = distance(array[0], str); 
        }
    }
    
    return min_dist_index;
}

void read_words_from_file(
char const *filename,
char **&word_array,
std::size_t &num_words,
std::size_t max_length
); //this function has already been implemented in main.cpp

void free_word_array( char** word_array ){
    delete[] word_array[0];
    word_array[0]= nullptr; //likely not necessary since pointer does not leave scope of fn. Would be better if the fn took ref to ptr.
    delete[] word_array;
    word_array = nullptr;
}
