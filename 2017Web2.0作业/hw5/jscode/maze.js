(function() {
    'use strict';
    const wallsID = ["up-part",
                     "left-part", 
                     "right-part",
                     "middle-middle-part", 
                     "bottom-part"];
    const gameStatus = {'GAMEWIN': 'You Win',
                      'GAMELOSE': 'You Lose', 
                      'DONOTCHEAT': "Don't cheat, you should start from the 'S' and move to the 'E' inside the maze!"};

    var isGameStart = false;    // check if game start
    var isGameCheat = false;    // check if player cheat

    document.getElementById('cheat-valid').onmouseenter = function() {
        if (isGameStart) {
            isGameCheat = true;
        }
    }
    
    const gameResult = document.getElementById('game-result');

    // set start event
    document.getElementById('start').onmouseenter = function() {
        isGameStart = true;         // game is on
        isGameCheat = false;        // player no cheat in the begining
        gameResult.innerText = "";  // empty the game result tip
    };

    // set end event
    document.getElementById('end').onmouseenter = function() {
        if (isGameStart) {          // if game is on
            isGameStart = false;    // end the game
            if (isGameCheat) {      // if player cheated in the game
                gameResult.innerText = gameStatus['DONOTCHEAT'];
                isGameCheat = false;
            } else {                // else player win the game
                gameResult.innerText = gameStatus['GAMEWIN'];
            }
        }
    };

    // set wall color
    // if mouse enter on one of the walls when the game is on, 
    // the wall entered on will turn in red and the player lose the game
    function wallTurnToRed(event) {
        if (isGameStart) {          // if game is on
            isGameStart = false;    // end the game
            event.target.className = 'red-wall-color';  // wall turn to red
            gameResult.innerText = gameStatus['GAMELOSE'];  // display game lose
        }
    }
    // if mouse leave the wall, the wall will restore
    function wallReturnToOrigin(event) {
        if (event.target.className === 'red-wall-color') {
            event.target.className = 'origin-wall-color';
        }
    }
    wallsID.forEach(function(wallID, index, array) {
        document.getElementById(wallID).onmouseenter = wallTurnToRed;
        document.getElementById(wallID).onmouseleave = wallReturnToOrigin;
    });
    
}());