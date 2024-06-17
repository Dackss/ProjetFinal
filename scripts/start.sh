#!/bin/bash

# ----------------------------------
# Projet Final - Généalogie
# Par: Thomas & Quentin
# ----------------------------------

# This function prints a header for the script.
# It uses escape codes to color the text green with the option echo -e.
print_header() {
    echo -e "\033[32m
 ____|                   _)  |          __ __|
 |       _\` |  __ \`__ \   |  |  |   |      |     __|   _ \   _ \   __|
 __|    (   |  |   |   |  |  |  |   |      |    |      __/   __/ \__ \\
_|     \__,_| _|  _|  _| _| _| \__, |     _|   _|    \___| \___| ____/
                               ____/
\033[0m"
}

# Same with this function, it uses escape codes to color the text.
# The menu is displayed.
show_menu() {
    echo -e "\033[34m---------------------------------\033[0m"
    echo -e "\033[33m           MENU PRINCIPAL        \033[0m"
    echo -e "\033[34m---------------------------------\033[0m"
    echo -e "\033[31m1. Afficher les informations d'une personne\033[0m"
    echo -e "\033[31m2. Afficher les enfants d'une personne\033[0m"
    echo -e "\033[31m3. Afficher les frères et sœurs d'une personne\033[0m"
    echo -e "\033[31m4. Afficher les ancêtres\033[0m"
    echo -e "\033[31m5. Exporter en HTML\033[0m"
    echo -e "\033[31m6. Quitter \033[0m"
    echo -e "\033[34m---------------------------------\033[0m"
    echo -e -n "\033[33mChoisissez une option: \033[0m"
}


# This function is used to pause the execution of the script until the user presses a key.
# The options allow to hide the input and to read only one character.
pause() {
    read -n 1 -s -r -p "Appuyez sur une touche pour continuer..."
}

# This function calls the ProjetFinal executable with the show_person_info command and the ID of the person to show.
show_person_info() {
    echo -n "Entrez l'ID de la personne: "
    read id
    ../cmake-build-debug/ProjetFinal show_person_info "$id"
    pause
}

# This function calls the ProjetFinal executable with the get_children command and the ID of the person to show the children.
get_children() {
    echo -n "Entrez l'ID de la personne: "
    read id
    ../cmake-build-debug/ProjetFinal get_children "$id"
    pause
}

# This function calls the ProjetFinal executable with the get_siblings command and the ID of the person to show the siblings.
get_siblings() {
    echo -n "Entrez l'ID de la personne: "
    read id
    ../cmake-build-debug/ProjetFinal get_siblings "$id"
    pause
}

# This function calls the ProjetFinal executable with the get_ancestors command and the ID of the person to show the ancestors.
get_ancestors() {
    echo -n "Entrez l'ID de la personne: "
    read id
    ../cmake-build-debug/ProjetFinal get_ancestors "$id"
    pause
}

# This function calls the ProjetFinal executable with the export_html command and the name of the output file.
export_html() {
    rm -f ../trees/result/*.html
    ../cmake-build-debug/ProjetFinal export_html "$filename"
    pause
}

# The function main of this script use a while loop to show the menu and read the user's choice.
main() {
    while true; do
        clear
        print_header
        show_menu
        read choice
        case $choice in
                1) show_person_info ;;
                2) get_children ;;
                3) get_siblings ;;
                4) get_ancestors ;;
                5) export_html ;;
                6) echo "Quitter..."; exit 0 ;;
                *) echo "Option invalide!"; pause ;;
        esac
    done
}

# Basically, this line calls the main function to start the script.
main