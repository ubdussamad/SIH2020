from django.shortcuts import render
from django.conf import settings
from django.http import HttpResponse, HttpResponseRedirect
import json
import os


def home(request):
    jsonFile = open(os.path.join(settings.STATIC_ROOT, 'data.json' )).read()
    jsonData = json.loads(jsonFile)
    for i in range(0, len(jsonData)):
        if (i == len(jsonData)-1):
            context = jsonData[i]
    return render(request, "device_feed/index.html", context)

def login(request):
    context = {}
    return render(request, "device_feed/login.html", context)

def auth(request):
    username_default = request.POST['username']
    password_default = request.POST['password']
    if (username_default == "admin"):
        if (password_default == "admin"):
            print("success")
            return HttpResponseRedirect('http://127.0.0.1:8000/')
        else:
            return ("Invalid Password")
    else:
        return ("Invalid Username")