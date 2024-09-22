#!/bin/bash

# Path to the template
TEMPLATE_PATH="Codeforces/CF Template/template.cpp"

# Function to create files A.cpp to X.cpp in a given directory
generate_files() {
    start_letter="A"
    end_letter=$1
    folder_path=$2
    mkdir -p "$folder_path"

    # Generate files from A.cpp to X.cpp using the template
    for letter in $(eval echo {$start_letter..$end_letter}); do
        cp "$TEMPLATE_PATH" "$folder_path/$letter.cpp"
    done

    # Create an empty in.txt file for input
    touch "$folder_path/in.txt"

    echo "Created contest files in $folder_path"
}

# Prompt the user for the contest type
echo "Enter the contest type (ABC, ARC, AGC, CF): "
read contest_type

# Prompt for contest round or name based on the type
case "$contest_type" in
    ABC)
        echo "Enter ABC round number: "
        read round_number
        generate_files "G" "AtCoder/ABC $round_number"
        ;;
    ARC)
        echo "Enter ARC round number: "
        read round_number
        generate_files "D" "AtCoder/ARC $round_number"
        ;;
    AGC)
        echo "Enter AGC round number: "
        read round_number
        generate_files "C" "AtCoder/AGC $round_number"
        ;;
    CF)
        echo "Enter Codeforces contest number or manual name (e.g., CF_123 or Ed_CF_456): "
        read contest_name
        echo "Enter the range of problems (default is A to E, leave blank for default): "
        read problem_range

        if [ -z "$problem_range" ]; then
            problem_range="E"
        fi

        generate_files "$problem_range" "Codeforces/$contest_name"
        ;;
    *)
        echo "Invalid contest type."
        ;;
esac
