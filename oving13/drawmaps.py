#!/usr/bin/python3
from selenium import webdriver
import time
import sys

pointlists = dict()
current_name = None
for line in sys.stdin:

    if line == "END\n":
        break
    elif not current_name:
        current_name = line
        pointlists[current_name] = ""
    elif line == "DIVIDER\n":
        current_name = None
    else:
        pointlists[current_name] += line

site = r"https://mapmakerapp.com/"

with webdriver.Chrome() as driver:
    driver.get(site)
    time.sleep(0.8)
    driver.find_element_by_xpath("//*[contains(text(), 'End Tour')]").click()
    time.sleep(0.3)

    driver.find_element_by_id("buttonMenuToggle").click()
    time.sleep(0.5)
    driver.find_element_by_class_name("openModalLogInSignUp").click()
    time.sleep(0.2)
    driver.find_element_by_xpath("//*[contains(text(),'Log In Here')]").click()
    time.sleep(0.2)
    email = driver.find_element_by_id("fieldLogInEmail")
    email.click()
    email.clear()
    email.send_keys("odderikf@stud.ntnu.no")
    passw = driver.find_element_by_id("fieldLogInPassword")
    passw.click()
    passw.clear()
    passw.send_keys(r"9xZ5XZm06@U@bs^Ue#131P%D")
    driver.find_element_by_id("buttonLogIn").click()

    time.sleep(8)

    driver.find_element_by_id("buttonMyMaps").click()
    time.sleep(0.5)
    driver.find_element_by_xpath("//img[@title='Delete Map']").click()
    time.sleep(0.1)
    driver.switch_to.alert.accept()

    time.sleep(8)

    entry_field = driver.find_element_by_id("fieldRapidEntry")
    add_to_map = driver.find_element_by_xpath("//*[contains(text(), 'Add To Map')]")
    count = 0
    for key, value in pointlists.items():
        entry_field.click()
        entry_field.clear()
        time.sleep(1.2)
        driver.execute_script("document.getElementById('fieldRapidEntry').value = arguments[0]", value)
        add_to_map.click()
        time.sleep(4)

        driver.find_element_by_xpath("//*[contains(text(), 'Unnamed')]").click()
        name_field = driver.find_element_by_id("fieldInlineEditLayerName")
        name_field.click()
        name_field.clear()
        name_field.send_keys(key)

        checkboxes = driver.find_elements_by_xpath("//input[@type='checkbox']")
        for c in checkboxes[6+count:9+count]:
            c.click()
        driver.find_element_by_id("buttonSaveInlineEditLayer").click()
        count += 1
        time.sleep(5)
    time.sleep(3600)
