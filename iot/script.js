//server status check
var xmlhttp = new XMLHttpRequest(); 
var url = "api/output.json"; 

xmlhttp.onreadystatechange = function() 
    { 
        if (xmlhttp.readyState == 4 && xmlhttp.status == 200) 
        { 
            var value = JSON.parse(xmlhttp.responseText);
            showValue(value); 
        } 
    }; 

xmlhttp.open("GET", url, true); 
xmlhttp.send();

function showValue(value)
{
    document.write(value.TimeStamp + '<br>');
    document.write(value.Temperature + '<br>');
    document.write(value.Brightness + '<br>');
    document.write(value.LightStatus + '<br>');
}
