#!/bin/bash

# Fonction pour afficher un en-tête avec de l'ASCII art
print_header() {
    echo "
 ____|                   _)  |          __ __|
 |       _\` |  __ \`__ \   |  |  |   |      |     __|   _ \   _ \   __|
 __|    (   |  |   |   |  |  |  |   |      |    |      __/   __/ \__ \\
_|     \__,_| _|  _|  _| _| _| \__, |     _|   _|    \___| \___| ____/
                               ____/
"
}

# Fonction pour afficher les détails d'une personne
print_person_details() {
    local person_id=$1
    echo "Affichage des détails de la personne avec ID $person_id"
    ../cmake-build-debug/ProjetFinal print_person_details $person_id
}

# Fonction pour afficher les enfants d'une personne
print_children() {
    local person_id=$1
    echo "Affichage des enfants de la personne avec ID $person_id"
    ../cmake-build-debug/ProjetFinal print_children $person_id
}

# Fonction pour afficher les frères et sœurs d'une personne
print_siblings() {
    local person_id=$1
    echo "Affichage des frères et sœurs de la personne avec ID $person_id"
    ../cmake-build-debug/ProjetFinal print_siblings $person_id
}

# Fonction pour démarrer l'animation de lien de la population
loading_icon() {
    local load_interval="${1}"
    local loading_message="${2}"
    local elapsed=0
    local loading_animation=( '—' "\\" '|' '/' )

    echo -n "${loading_message} "

    # This part is to make the cursor not blink
    # on top of the animation while it lasts
    tput civis
    trap "tput cnorm" EXIT
    while [ "${load_interval}" -ne "${elapsed}" ]; do
        for frame in "${loading_animation[@]}" ; do
            printf "%s\b" "${frame}"
            sleep 0.25
        done
        elapsed=$(( elapsed + 1 ))
    done
    printf " \b\n"
}

link_population() {
    # Print progress
    echo -n "Linking populations in progress... "

    loading_icon 2

    echo -e "\bLinking done!"
    sleep 1
}

# Afficher le menu et gérer les choix de l'utilisateur
start_menu() {
    clear
    print_header
    link_population
    while true; do
        clear
        print_header
        echo "Menu:"
        echo "1. Afficher les détails d'une personne"
        echo "2. Afficher les enfants d'une personne"
        echo "3. Afficher les frères et sœurs d'une personne"
        echo "4. Quitter"
        echo -n "Entrez votre choix: "
        read choice

        case $choice in
            1)
                echo -n "Entrez l'ID de la personne: "
                read person_id
                print_person_details $person_id
                read -p "Appuyez sur une touche pour continuer..."
                ;;
            2)
                echo -n "Entrez l'ID de la personne: "
                read person_id
                print_children $person_id
                read -p "Appuyez sur une touche pour continuer..."
                ;;
            3)
                echo -n "Entrez l'ID de la personne: "
                read person_id
                print_siblings $person_id
                read -p "Appuyez sur une touche pour continuer..."
                ;;
            4)
                echo "Au revoir!"
                exit 0
                ;;
            *)
                echo "Choix invalide, veuillez réessayer."
                read -p "Appuyez sur une touche pour continuer..."
                ;;
        esac
    done
}

# Vérifier si l'exécutable existe
if [ ! -f ../cmake-build-debug/ProjetFinal ]; then
    echo "L'éxécutable ProjetFinal n'existe pas. Veuillez compiler le projet d'abord."
    exit 1
fi

# Vérifier si des arguments sont fournis
if [ $# -eq 0 ]; then
    # Aucun argument fourni, lancer le menu
    start_menu
else
    # Passer les arguments à l'exécutable
    ../cmake-build-debug/ProjetFinal "$@"
fi
