from django.shortcuts import render
# from django.http import HttpResponse
from .models import Post
import json


def home(request):
    context = {
        "posts" : Post.objects.all()
    }
    return render(request, "blog/index.html", context)

