from django.shortcuts import render
from django.conf import settings
import json
import os


def home(request):
    # jsonFile = open(os.path.join(settings.STATIC_ROOT, 'data.json' )).read()
    # jsonData = json.loads(jsonFile)
    # for i in range(0, len(jsonData)):
    #     if (i == len(jsonData)-1):
    #         context = jsonData[i]

    context = {
        'deviceID':'123',
        'currentLevel': '22',
        'maxLevel': '2',
        'minLevel': '2'
    }
    
    return render(request, "device_feed/index.html", context)

