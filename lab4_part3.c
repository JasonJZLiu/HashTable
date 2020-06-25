#include "lab4.h"


long int file_line_counter(char* fn){
    long int count = 0;
    FILE* input_stream = fopen(fn, "r");
    char c;
    if (input_stream == NULL)
    {
        return 0;
    }
    for (c = getc(input_stream); c != EOF; c = getc(input_stream)){
        if (c == '\n'){
            count += 1;
        }
    }
    fclose(input_stream);
    return count;
}

PersonalData** parse_data(char* fn){
    long int line_count = file_line_counter (fn);
    //printf ("line_count %d \n", line_count);

    FILE* input_stream = fopen(fn, "r");
    char first_line[100];
    fgets(first_line, sizeof(first_line), input_stream);

    PersonalData** PD_ptr_array = malloc(sizeof(PersonalData*)*line_count);
    for (long int i = 0; i < line_count; i++){
        PersonalData* data = malloc(sizeof(PersonalData));
        fscanf(input_stream, "%lu\t%c\t%s\t%s\t%s\t%s\t%d-%d-%d", &(data -> SIN), &(data -> gender), data -> first_name, data -> last_name, data -> passport_num, data -> bank_acc_num, &(data -> dob_year), &(data -> dob_month), &(data -> dob_day));
        PD_ptr_array[i] = data;
    }

    fclose(input_stream);
    return PD_ptr_array;
}


void counter_intelligence(char* load, char* update, char* validate, char* outfile){
    HashTable* load_hash = create_hash_table(0, CLOSED_ADDRESSING); //require deleting;

    PersonalData** load_arr = parse_data(load); //require deleting;
    long int loadcount = file_line_counter (load);
    for (long int i = 0; i < loadcount; i++){
        update_key(load_arr[i], &load_hash);
    }

    long int updatecount = file_line_counter (update);
    PersonalData** update_arr = parse_data(update); //require deleting;
    for (long int i = 0; i < updatecount; i++){
        update_key(update_arr[i], &load_hash);
    }


    FILE* output_stream = fopen(outfile, "w");

    long int validatecount = file_line_counter (validate);
    PersonalData** validate_arr = parse_data(validate); //require deleting;
    for (long int i = 0; i < validatecount; i++){
        int flag = 0;
        PersonalData* data_in_hash = lookup_key(validate_arr[i]->SIN, load_hash);
        if (data_in_hash){
            //print_personal_data(data_in_hash);
            //printf ("%d \n", validate_arr[k]->SIN);
            //printf ("%c \n", validate_arr[k] -> gender);
            if (data_in_hash -> gender != validate_arr[i] -> gender){
                flag = 1;
            }
            if (strcmp(data_in_hash -> first_name, validate_arr[i] -> first_name) != 0) {
                flag = 1;
            }
            if (strcmp(data_in_hash -> last_name, validate_arr[i] -> last_name) != 0) {
                flag = 1;
            }
            if (strcmp(data_in_hash -> passport_num, validate_arr[i] -> passport_num) != 0) {
                flag = 1;
            }
            if (strcmp(data_in_hash -> bank_acc_num, validate_arr[i] -> bank_acc_num) != 0) {
                flag = 1;
            }
            if (data_in_hash -> dob_year != validate_arr[i] -> dob_year) {
                flag = 1;
            }
            if (data_in_hash -> dob_month != validate_arr[i] -> dob_month) {
                flag = 1;
            }
            if (data_in_hash -> dob_day != validate_arr[i] -> dob_day) {
                flag = 1;
            }

            if (flag == 1){
                fprintf(output_stream, "%lu\n", validate_arr[i]->SIN);
            }

        }
    }
    fclose(output_stream);

    delete_table(load_hash);

    for (long int i = 0; i < loadcount; i++){
        free(load_arr[i]);
    }
    free(load_arr);
    load_arr = NULL;

    for (long int i = 0; i < updatecount; i++){
        free(update_arr[i]);
    }
    free(update_arr);
    update_arr = NULL;

    for (long int i = 0; i < validatecount; i++){
        free(validate_arr[i]);
    }
    free(validate_arr);
    validate_arr = NULL;
}



int main (){
    //gcc -o test3 lab4.h lab4_part1.c lab4_part2.c lab4_part3.c utilities.c utilities.h

    counter_intelligence ("full_data_LOAD.txt", "full_data_UPDATE.txt", "full_data_VALIDATE.txt", "spies.txt");
}





