(function () {
    'use strict';
    // the position of [id]th li
    var positionOf = new Array(16),
        offsetOf = new Array(16),   // correct offset of li
        curOffsetOf = new Array(16),
        isFirstTime = true,         // is thr first time to start the game
        timeCounterID;
    const timeCounter = document.getElementById('Time'),
           stepsCounter = document.getElementById('Steps');
    // initial positionOf
    // [15, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14]
    function initialPositionOf() {
        positionOf[0] = 15;  // positionOf[0] empty block
        for (var i = 1; i < 16; i++) {  // initial positions
            positionOf[i] = i - 1;
        }
    }

    // chenk if win and alert
    function isWinByPositionOf() {
        var j = 0;
        for (j = 0; j < 16; j++) {
            if (positionOf[j] != j) {
                break;
            }
        }
        if (j == 16) {
            setTimeout(function () {
                alert("You win!");
                clearInterval(timeCounterID);   // stop time count 
            }, 600);
        }
    }

    // ---------------------------------------------------
    $(function () {
        document.getElementById('thumbnail').style.backgroundImage = 'url(imgs/panda.jpg)';
        document.getElementById("thumbnail").style.backgroundSize = "200px 200px";
        initialPositionOf();
        // generate puzzles
        var $ul = $('<ul>', { 'class': 'puzzle-container' }),
            $li,
            i;

        for (i = 0; i < 15; i++) {
            $li = $('<li>', {
                'id': i + 1,
                'class': 'puzzle-block',
                css: {
                    'left': i % 4 * (95 + 1.5) + 1.5 + 'px',
                    'top': Math.floor(i / 4) * (95 + 1.5) + 1.5 + 'px',
                    'background': 'url(imgs/panda.jpg)',
                    'background-position': (4 - i % 4) * 95 + 'px ' + (4 - Math.floor(i / 4) % 4) * 95 + 'px'
                }
            });

            $li.click(function () {
                var thisOffset = curOffsetOf[$(this).attr('id')],
                    emptyOffset = $('#0').offset();
                if (Math.abs(emptyOffset.left - thisOffset.left) + Math.abs(emptyOffset.top - thisOffset.top) < 140) {
                    // move the block
                    $(this).animate({
                        left: "+=" + (emptyOffset.left - thisOffset.left) + "px",
                        top: "+=" + (emptyOffset.top - thisOffset.top) + "px"
                    }, 100);
                    curOffsetOf[$(this).attr('id')] = emptyOffset;
                    // move empty block
                    $('#0').offset(thisOffset);
                    // change position list
                    var tmp = positionOf[0];
                    positionOf[0] = positionOf[$(this).attr('id')];
                    positionOf[$(this).attr('id')] = tmp;
                    ++stepsCounter.innerText;
                    // chenk if win
                    isWinByPositionOf();
                }
            });
            $ul.append($li);
        }

        // add empty block
        $li = $('<li>', {
            'id': 0,
            'class': 'empty-block',//'empty-block',
            css: {
                'left': i % 4 * (95 + 1.5) + 1.5 + 'px',
                'top': Math.floor(i / 4) * (95 + 1.5) + 1.5 + 'px'
            }
        });
        $ul.append($li);
        $('#puzzle-position').append($ul);

        // first play the game
        function firstPlayGame() {
            isFirstTime = false;
            for (i = 0; i < 16; i++) {
                offsetOf[i] = $('#' + i).offset();
            }
            curOffsetOf = offsetOf.slice();
        }
        // random the array
        function generateRandomPuzzleArray() {
            var positionOfTmp = new Array(16),
                count = 15,
                randomNum;
            // positionOfTmp[0] = 15;
            // positionOf[0] = undefined;
            while (count >= 0) {
                randomNum = Math.floor(Math.random() * 16);
                if (positionOf[randomNum] >= 0) {
                    positionOfTmp[count] = positionOf[randomNum];
                    positionOf[randomNum] = undefined;
                    --count;
                }
            }
            return positionOfTmp;
        }
        // check if puzzle is valid
        function ifPuzzleArrayValid(positionOfTmp) {
            var i,
                j,
                ans = 6 - positionOfTmp[0] % 4 - Math.floor(positionOfTmp[0] / 4);
            for (i = 0; i < 16; i++) {
                for (j = 0; j < i; j++) {
                    if (positionOfTmp[j] < positionOfTmp[i]) {
                        ++ans;
                    }
                }
            }
            return ans & 1 > 0 ? true : false;
        }
        // move puzzle by positionOf
        function movePuzzlebyPositionOf() {
            var newOffset,
                curOffset,
                i;
            for (i = 0; i < 16; i++) {
                newOffset = offsetOf[positionOf[i]];
                curOffset = curOffsetOf[i];//$('#' + i).offset();
                $('#' + i).animate({
                    left: "+=" + (newOffset.left - curOffset.left) + "px",
                    top: "+=" + (newOffset.top - curOffset.top) + "px"
                }, 2);
                curOffsetOf[i] = newOffset;
            }
        }

        function timeCount() {
            ++timeCounter.innerText;
        }
        // restart button--random puzzle
        $('#restart').click(function () {
            if (isFirstTime) {
                firstPlayGame();
            }
            // find a solvable random puzzle
            while (true) {
                positionOf = generateRandomPuzzleArray().slice();
                if (ifPuzzleArrayValid(positionOf)) {
                    break;
                }
            }
            // move puzzle by positionOf
            movePuzzlebyPositionOf();
            timeCounterID = setInterval(timeCount, 1000);
            stepsCounter.innerText = "0";
            timeCounter.innerText = "0";
        });

    });
    // --------------------------------------------------------------

}());