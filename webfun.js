
var option="Forward"
var words;
$(document).ready(function () {

    $('#search').keyup(findMatches);
    $('#random-btn').click(randomWord);
    $("#inputText").keyup(showstuff);

    $(".dropdown-menu a").click(function(){
	console.log("pick!"+$(this).text());
	$(this).parents(".dropdown").find(".selection").text($(this).text());
	option=$(this).text();
    showstuff();
    });

});

jQuery.get('http://jimskon.com/class/softdev/skon/webfun/words.txt', function(data) {
   saveWords(data)
}, 'text');

function saveWords(data) {
  words=data.split("\n");
}

function reverse(str) {
  var newString = "";
  for (var i = str.length-1; i >= 0; i--) {
      newString += str[i];
  }
  return newString;
}

function even(str) {
  var newString = "";
  for (var i = str.length-1; i >= 0; i--) {
    if (i%2==0) {
      newString += str[i];
    }
  }
  return newString;
}

function sortString(text) {
    return text.split('').sort().join('');
};

function showstuff() {
  var intext = $("#inputText").val();
  if (option=="Backward") {
    intext=reverse(intext);
  } else if (option=="Sort") {
    intext=sortString(intext);
  }
  console.log(intext);
  $("#outputText").val(intext);
}

function binarySearch(ar, el) {
    var m = 0;
    var n = ar.length - 1;
    var k;
    while (m <= n) {
        k = (n + m) >> 1;
       if (el>ar[k]) {
            m = k + 1;
        } else if(el<ar[k]) {
            n = k - 1;
        } else {
            return k;
        }
    }
    return k;
}

function findMatches() {
  word=$("#search").val().toLowerCase();
  var i=binarySearch(words,word);

  start=Math.max(i-5,0);
  out="";
  j=start;
  while (j<start+10) {
    out+=words[j]+"<br/>";

    j++;
  }
  $('#wordmatches').html(out);
}

function randomWord() {
  i=Math.floor(Math.random() * words.length);
  $("#search").val(words[i]);
  findMatches();
}
