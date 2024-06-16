#!/bin/bash

show_menu() {
    echo "---------------------------------"
    echo "           MENU PRINCIPAL        "
    echo "---------------------------------"
    echo "1. Afficher les informations d'une personne"
    echo "2. Afficher les enfants d'une personne"
    echo "3. Afficher les frères et sœurs d'une personne"
    echo "4. Afficher les ancêtres"
    echo "5. Exporter en HTML"
    echo "6. Quitter"
    echo "---------------------------------"
    echo -n "Choisissez une option: "
}

pause() {
    read -n 1 -s -r -p "Appuyez sur une touche pour continuer..."
}

show_person_info() {
    echo -n "Entrez l'ID de la personne: "
    read id
    ../cmake-build-debug/ProjetFinal show_person_info "$id"
    pause
}

get_children() {
    echo -n "Entrez l'ID de la personne: "
    read id
    ../cmake-build-debug/ProjetFinal get_children "$id"
    pause
}

get_siblings() {
    echo -n "Entrez l'ID de la personne: "
    read id
    ../cmake-build-debug/ProjetFinal get_siblings "$id"
    pause
}

get_ancestors() {
    echo -n "Entrez l'ID de la personne: "
    read id
    ../cmake-build-debug/ProjetFinal get_ancestors "$id"
    pause
}

export_html() {
    echo -n "Entrez le nom du fichier de sortie HTML: "
    read filename
    ../cmake-build-debug/ProjetFinal export_html "$filename"
    pause
}

main() {
    while true; do
        clear
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

# Passer les paramètres à la fonction principale
main "$@"