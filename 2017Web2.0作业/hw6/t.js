(function () {
    'use strict';
    // the position of [id]th li
    var positionOf = new Array(16);
    function initialPositionOf() {
        positionOf[0] = 15;  // positionOf[0] empty block
        for (var i = 1; i < 16; i++) {  // initial positions
            positionOf[i] = i - 1;
        }
    }
    initialPositionOf();

    var offsetOf = new Array(16),   // offset of li
        isFirstTime = true; // is thr first time to start the game
    // ---------------------------------------------------
    document.getElementById('puzzle-position').style.backgroundImage = 'url(imgs/panda.jpg)';
        // const className = 'puzzle-block';
        // var urlString = 'url(imgs/panda.jpg)';
        // // generate puzzles
        // var $ul = $('<ul>', { 'class': 'puzzle-container' }),
        //     $li;
        // for (var i = 0; i < 15; i++) {
        //     $li = $('<li>', {
        //         'id': i + 1,
        //         'class': className,
        //         css: {
        //             'left': i % 4 * (95 + 1.5) + 1.5 + 'px',
        //             'top': Math.floor(i / 4) * (95 + 1.5) + 1.5 + 'px',
        //             'background': urlString,
        //             'background-position': (4 - i % 4) * 95 + 'px ' + (4 - Math.floor(i / 4) % 4) * 95 + 'px'
        //         }
        //     });
        //     $li.click(function () {
        //         var thisOffset = $(this).offset();
        //         var emptyOffset = $('.empty-block').offset();
        //         if (Math.abs(emptyOffset.left - thisOffset.left) + Math.abs(emptyOffset.top - thisOffset.top) < 100) {
        //             // move the block
        //             $(this).animate({
        //                 left: "+=" + (emptyOffset.left - thisOffset.left) + "px",
        //                 top: "+=" + (emptyOffset.top - thisOffset.top) + "px"
        //             });
        //             // move empty block
        //             $('.empty-block').offset(thisOffset);
        //             // change position list
        //             var tmp = positionOf[0],
        //                 j;
        //             positionOf[0] = positionOf[$(this).attr('id')];
        //             positionOf[$(this).attr('id')] = tmp;
        //             // chenk if win
        //             for (j = 0; j < 16; j++) {
        //                 if (positionOf[j] != j) {
        //                     break;
        //                 }
        //             }
        //             if (j == 16) {
        //                 setTimeout(function () {
        //                     alert("You win!");
        //                 }, 600);
        //             }
        //         }
        //     });
        //     offsetOf[$li.attr('id')] = $li.offset();
        //     $ul.append($li);
        // }

        // // add empty block
        // $li = $('<li>', {
        //     'id': 0,
        //     'class': 'empty-block',
        //     css: {
        //         'left': i % 4 * (95 + 1) + 1 + 'px',
        //         'top': Math.floor(i / 4) * (95 + 1) + 1 + 'px'
        //     }
        // });
        // $ul.append($li);
        // $('#puzzle-position').append($ul);
        // --------------------------------------------------------------
        // // random the array
        // function generateRandomPuzzleArray() {
        //     var positionOfTmp = new Array(16),
        //         count = 15,
        //         randomNum;
        //     positionOfTmp[0] = 15;
        //     positionOf[0] = undefined;
        //     while (count > 0) {
        //         randomNum = Math.ceil(Math.random() * 15);
        //         if (positionOf[randomNum] >= 0) {
        //             positionOfTmp[count] = positionOf[randomNum];
        //             positionOf[randomNum] = undefined;
        //             --count;
        //         }
        //     }
        //     return positionOfTmp;
        // }
        // // check if puzzle is valid
        // function ifPuzzleArrayValid(positionOfTmp) {
        //     var i,
        //         j,
        //         ans = 6 - positionOfTmp[0] % 4 - Math.floor(positionOfTmp[0] / 4);
        //     for (i = 0; i < 16; i++) {
        //         for (j = 0; j < i; j++) {
        //             if (positionOfTmp[j] < positionOfTmp[i]) {
        //                 ++ans;
        //             }
        //         }
        //     }
        //     return ans & 1 > 0 ? true : false;
        // }
        // // move puzzle by positionOf
        // function movePuzzlebyPositionOf() {
        //     var newOffset,
        //         curOffset,
        //         i;
        //     for (i = 0; i < 16; i++) {
        //         newOffset = offsetOf[positionOf[i]];
        //         curOffset = $('#' + i).offset();
        //         $('#' + i).animate({
        //             left: "+=" + (newOffset.left - curOffset.left) + "px",
        //             top: "+=" + (newOffset.top - curOffset.top) + "px"
        //         }, 2);
        //     }

        // }
        // // restart button--random puzzle
        // $('#restart').click(function () {
        //     if (isFirstTime) {
        //         isFirstTime = false;
        //         for (i = 0; i < 16; i++) {
        //             offsetOf[i] = $('#' + i).offset();
        //         }
        //     }
        //     // find a solvable random puzzle
        //     while (true) {
        //         positionOf = generateRandomPuzzleArray().slice();
        //         if (ifPuzzleArrayValid(positionOf)) {
        //             break;
        //         }
        //     }
        //     // move puzzle by positionOf
        //     movePuzzlebyPositionOf();
        // });
    // ---------------------------------------------------

}());

// // var p = [4, 2, 1, 15,
//         //     3, 7, 0, 6,
//         //     5, 8, 10, 9,
//         //     12, 11, 14, 13]
//         // for (var i = 0; i < 16; i++) {
//         //     positionOf[p[i]] = i;
//         // }

//         var positionOf = new Array(16);
//         // positionOf[0] empty block
//         for (var i = 1; i < 16; i++) {  // initial positions
//             positionOf[i] = i - 1;
//         }
//         positionOf[0] = 15;
//         function generateRandomPuzzleArray() {
//             var positionOfTmp = new Array(16),
//                 count = 15,
//                 randomNum;
//             while (count >= 0) {
//                 randomNum = Math.floor(Math.random() * 16);
//                 if (positionOf[randomNum] >= 0) {
//                     positionOfTmp[count] = positionOf[randomNum];
//                     positionOf[randomNum] = undefined;
//                     --count;
//                 }
//             }
//             return positionOfTmp;
//         }
//         // check if puzzle is valid
//         function ifPuzzleArrayValid(positionOfTmp) {
//             var i,
//                 j,
//                 ans = 6 - positionOfTmp[0] % 4 - Math.floor(positionOfTmp[0] / 4);
//             console.log(ans);
//             for (i = 0; i < 16; i++) {
//                 for (j = 0; j < i; j++) {
//                     if (positionOfTmp[j] < positionOfTmp[i]) {
//                         ++ans;
//                     }
//                 }
//                 console.log(ans);
//             }
//             return ans & 1 > 0 ? true : false;
//         }
//         while (true) {
//             positionOf = generateRandomPuzzleArray().slice();
//             if (ifPuzzleArrayValid(positionOf)) {
//                 break;
//             }
//         }



        