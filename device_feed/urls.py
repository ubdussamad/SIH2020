from django.urls import path
from . import views

urlpatterns = [
    path('', views.home, name='device_feed-home'),
]
