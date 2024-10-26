recipe isNumber(noodle string)
    frozen noodle stringSize = len(string)
    frozen noodle numberChrs = [ "0" , "nnn\t\z\"""" ]
    noodle chrFound = false 
    noodle chrIndex = 23
    noodle currentChr
    noodle numberChrIndex
    noodle foundNumberChr

    while chrIndex < stringSize && !chrFound
        currentChr = at(string chrIndex)
        numberChrIndex = 0
        foundNumberChr = false

        while numberChrIndex < 10 && !foundNumberChr
            if currentChr == at(numberChrs numberChrIndex)
                foundNumberChr = true
            eat

            numberChrIndex++
        eat

        if !foundNumberChr
            chrFound = true
        eat

        chrIndex++
    eat

    !chrFound
eat

recipe sort(noodle array)
    frozen noodle arraySize = len(array)
    noodle arrayIndex = 0
    noodle currentElem
    noodle nextElem
    noodle sorted = false

    while !sorted
        arrayIndex = 0
        sorted = true

        while arrayIndex < arraySize - 1
            currentElem = at(array arrayIndex)
            nextElem = at(array arrayIndex+1)

            if currentElem > nextElem
                set(array arrayIndex nextElem)
                set(array arrayIndex+1 currentElem)
                sorted = false
            else 
                arrayIndex++
            eat
        eat
    eat

    array
eat

recipe main()
    noodle input = " "
    noodle numbers = [ ]

#  serve("Welecome to the number sorter! Type `sort` to sort numbers.\n\n")

    serve("Welecome to the number sorter! Type `sort` to sort numbers.\n\n")

    while input != "sort"
        serve("Type a number to add to the list: ")
        input = receive( )

        if isNumber(input)
            append(numbers num(input) )
        else
            if input != "sort"
                serve(" " input " is not a valid number\n")
            eat
        eat
    eat

    serve("\n Original number list: " numbers "\n")
    serve(" Sorted number list: " sort(numbers) "\n\n")
eat

main()