export DEP_PATH="$PWD/examples/dependencies"

export RETURN_MESSAGE="No changes"

directory_exists()
{
    test -d "$1"
}

! directory_exists "$DEP_PATH" && mkdir "$DEP_PATH"

cd "$DEP_PATH" || exit

! directory_exists "$PWD/glfw" && git clone https://github.com/glfw/glfw.git && export RETURN_MESSAGE="Updated"
! directory_exists "$PWD/glm" && git clone https://github.com/g-truc/glm.git && export RETURN_MESSAGE="Updated"
! directory_exists "$PWD/glm" && git clone https://github.com/gilmar-sales/glad.git && export RETURN_MESSAGE="Updated"

echo "$RETURN_MESSAGE"
