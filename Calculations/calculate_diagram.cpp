#include "calculate_diagram.hpp"
#include <vector>
#include <algorithm>

std::string gene_data_to_string(const single_gene_data & gd){
    std::string result = "";
    if(gd.codominant == false){
        if(gd.gamete_description.domination_type == GAMETE_DOMINATION_TYPE::DOMINANT){
            result = toupper(gd.letter);
        }
        else if(gd.gamete_description.domination_type == GAMETE_DOMINATION_TYPE::RECESIVE){
            result = tolower(gd.letter);
        }
    }
    else{
        if(gd.gamete_description.codomination_index == 0){
            result = tolower(gd.letter);
        }
        else{
            result = std::string(1, toupper(gd.letter)) + "<sub>" + std::to_string(gd.gamete_description.codomination_index) + "</sub>";
        }
    }
    return result;
}

std::string gamete_to_string(const whole_gamete & ga){
    std::string result = "";
    for(auto & r : ga){
        result += gene_data_to_string(r);
    }
    return result;
}

bool single_gene_compare(single_gene_data & lhs, single_gene_data & rhs){
    if(lhs.letter < rhs.letter) return true;
    if(lhs.letter > rhs.letter) return false;
    if(lhs.codominant == true and rhs.codominant == true){
        if(lhs.gamete_description.codomination_index == 0) return false;
        return lhs.gamete_description.codomination_index < rhs.gamete_description.codomination_index;
    }
    if(lhs.gamete_description.domination_type == GAMETE_DOMINATION_TYPE::DOMINANT 
    and rhs.gamete_description.domination_type == GAMETE_DOMINATION_TYPE::RECESIVE){
        return true;
    }
    if(lhs.gamete_description.domination_type == GAMETE_DOMINATION_TYPE::RECESIVE 
    and rhs.gamete_description.domination_type == GAMETE_DOMINATION_TYPE::DOMINANT){
        return false;
    }
    return true;
}

calculation_results calculate_diagram(const GENE_DATA & gene_data){
    unsigned n_genes = gene_data.size();
    #if DEBUG_MODE
        std::cout << "Number of separate genes: " << gene_data.size() << std::endl;
    #endif
    unsigned sq_size = 2 << (n_genes - 1);

    std::vector<whole_gamete> gametes_1(sq_size);
    std::vector<whole_gamete> gametes_2(sq_size); 

    for(auto & obj : gametes_1)
        obj.resize(n_genes);
    for(auto & obj : gametes_2)
        obj.resize(n_genes);

    #if DEBUG_MODE
        std::cout << "n_genes: " << n_genes << std::endl;
        std::cout << "sq_size: " << sq_size << std::endl;
    #endif

    //fill in gamete types of the first parent's genotype
    for(unsigned i = 0; i < sq_size; i++){
        auto gene_iter = gene_data.begin();
        for(unsigned j = 0; j < n_genes; j++){
            std::cout << "I, J" << i << "," << j << std::endl;
            //take first gene version or second one?
            bool take = ((1 << j) & i) != 0 ? false : true;

            if(take){
                gametes_1.at(i).at(j).letter = gene_iter->first;
                gametes_1.at(i).at(j).gamete_description = gene_iter->second.gamete1;

                gametes_2.at(i).at(j).letter = gene_iter->first;
                gametes_2.at(i).at(j).gamete_description = gene_iter->second.gamete1_2;
            }
            else{
                gametes_1.at(i).at(j).letter = gene_iter->first;
                gametes_1.at(i).at(j).gamete_description = gene_iter->second.gamete2;

                gametes_2.at(i).at(j).letter = gene_iter->first;
                gametes_2.at(i).at(j).gamete_description = gene_iter->second.gamete2_2;
            }

            if(gene_iter->second.dtype == GENE_DOMINATION_TYPE::CO){
                gametes_1.at(i).at(j).codominant = true;
                gametes_2.at(i).at(j).codominant = true;
            }
            else{
                gametes_1.at(i).at(j).codominant = false;
                gametes_2.at(i).at(j).codominant = false;
            }

            gene_iter++;
        }

        std::sort(gametes_1.at(i).begin(), gametes_1.at(i).end(), single_gene_compare);
        std::sort(gametes_2.at(i).begin(), gametes_2.at(i).end(), single_gene_compare);
    }

    #if DEBUG_MODE
        std::cout << "Gamete versions:" << std::endl << "Gametes 1: ";
        for(auto & gamete : gametes_1){
            for(auto & l : gamete){
                std::cout << gene_data_to_string(l);
            }
            std::cout << ", ";
        }
        std::cout << std::endl << "Gametes 2: ";
        for(auto & gamete : gametes_2){
            for(auto & l : gamete){
                std::cout << gene_data_to_string(l);
            }
            std::cout << ", ";
        }
        std::cout << std::endl;
    #endif

    calculation_results c_results;
    std::vector<std::vector<std::vector<single_gene_data>>> calculation_raw(sq_size);

    c_results.c_results.resize(sq_size);

    for(auto & obj : c_results.c_results)
        obj.resize(sq_size);

    for(auto & obj : calculation_raw)
        obj.resize(sq_size);

    for(unsigned i = 0; i < sq_size; i++){
        for(unsigned j = 0 ; j < sq_size; j++){
            calculation_raw.at(i).at(j).reserve(n_genes);
            for(unsigned y = 0; y < n_genes; y++){
                if(single_gene_compare(gametes_1.at(j).at(y), gametes_2.at(i).at(y))){
                    calculation_raw.at(i).at(j).push_back(gametes_1.at(j).at(y));
                    calculation_raw.at(i).at(j).push_back(gametes_2.at(i).at(y));
                }
                else{
                    calculation_raw.at(i).at(j).push_back(gametes_2.at(i).at(y));     
                    calculation_raw.at(i).at(j).push_back(gametes_1.at(j).at(y));
                }

            }
        }
    }

    for(unsigned i = 0; i < sq_size; i++){
        for(unsigned j = 0 ; j < sq_size; j++){
            c_results.c_results.at(i).at(j).string_representation = "";
            for(unsigned y = 0; y < n_genes*2; y++){
                c_results.c_results.at(i).at(j).string_representation +=
                    gene_data_to_string(calculation_raw.at(i).at(j).at(y));
            }
            #if DEBUG_MODE
                std::cout << c_results.c_results.at(i).at(j).string_representation << ", ";
            #endif
        }
        #if DEBUG_MODE
            std::cout << std::endl;
        #endif
    }

    c_results.gametes1 = std::move(gametes_1);
    c_results.gametes2 = std::move(gametes_2);

    return c_results;
    
}
