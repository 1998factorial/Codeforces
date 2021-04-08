import math

# EARTH_R = 6353 * 1000
EARTH_R = 1
CITIES = []
SATTELITE = []

def feq(a, b):
  return abs(a - b) <= 1e-6

def max(a , b):
    if a > b:
        return a
    return b

def min(a , b):
    if a < b:
        return a
    return b

def fleq(a , b):
    if a <= b:
        return 1
    return abs(a - b) <= 1e-6

def fgtq(a , b):
    if a >= b:
        return 1
    return abs(a - b) <= 1e-6

def city (name, theta):
    global CITIES
    CITIES.append({
        'name': name,
        'theta' : theta
    })
    return {}

def show_city():
    return CITIES

def sattelite (height, velocity, theta):
    global SATTELITE
    SATTELITE.append({
        'height': height,
        'velocity' : velocity,
        'theta' : theta
    })
    return {}

def show_sattelite():
    return SATTELITE

# /simulate
def simulate():
    # step 1: convert all cities to (x , y) coordinates
    cities = []
    ret = []
    for city in CITIES:
        cities.append({
            'name' : city['name'] ,
            'x' : math.cos(city['theta']) * EARTH_R ,
            'y' : math.sin(city['theta']) * EARTH_R
        })
        ret.append({
            'city_name' : city['name'] ,
            'blackout_intervals' : 0
        })
    # step 2: compute the initial coordinates of sattelites
    sattelites = []
    for sattelite in SATTELITE:
        radius = EARTH_R + sattelite['height']
        sattelites.append({
            'v' : (60.0 * sattelite['velocity']) / radius , # change of theta per mintue
            'h' : radius ,
            'theta' : sattelite['theta'] ,
            'x' : math.cos(sattelite['theta']) * radius ,
            'y' : math.sin(sattelite['theta']) * radius
        })
    for time in range(1 , 1441):
        # update sattelite coordinates
        for sattelite in sattelites:
            sattelite['theta'] += sattelite['v']
            sattelite['x'] = math.cos(sattelite['theta']) * sattelite['h']
            sattelite['y'] = math.sin(sattelite['theta']) * sattelite['h']
        for city in cities:
            ok = 0
            x1 = 1.0 * city['x']
            y1 = 1.0 * city['y']
            # check if there exist a sattlite that is visible by this city
            for sattelite in sattelites:
                x2 = 1.0 * sattelite['x']
                y2 = 1.0 * sattelite['y']
                k = 1.0 * (y1 - y2) / (x1 - x2)
                b = y1 - k * x1
                # (k^2 + 1) * x^2 + (2kb)x + (b^2 - R^2) = 0
                # ax^2 + bx + c = 0
                # we now check the discriminant
                A = 1.0 * k * k + 1
                B = 2.0 * k * b
                C = 1.0 * b * b - EARTH_R * EARTH_R
                # d = (4.0 * k * k * b * b) - (4.0 * (b * b - EARTH_R * EARTH_R) * (k * k + 1))
                D = B * B - 4.0 * A * C
                if D < 0:
                    continue
                elif D == 0:
                    ok = 1
                else:
                    # we solve for these 2 intersection points
                    # both of them must be bounded by (x1 , y1) and (x2 , y2)
                    xx1 = (-B + math.sqrt(D)) / (2.0 * A)
                    yy1 = 1.0 * k * xx1 + b
                    xx2 = (-B - math.sqrt(D)) / (2.0 * A)
                    yy2 = 1.0 * k * xx2 + b
                    print(f"x1 = {x1}, y1 = {y1}, x2 = {x2}, y2 = {y2}")
                    print(f"xx1 = {xx1}, yy1 = {yy1}, xx2 = {xx2}, yy2 = {yy2}")
                    count = 0
                    if fleq(min(x1 , x2) , xx1) and fleq(xx1 , max(x1 , x2)) and fleq(min(y1 , y2) , yy1) and fleq(yy1 , max(y1 , y2)):
                        count += 1
                    if fleq(min(x1 , x2) , xx2) and fleq(xx2 , max(x1 , x2)) and fleq(min(y1 , y2) , yy2) and fleq(yy2 , max(y1 , y2)):
                        count += 1
                    if count < 2:
                        ok = 1
                    print(count)
            if ok == 0:
                for val in ret:
                    if val['city_name'] == city['name']:
                        val['blackout_intervals'] += 1
    ans = []
    for val in ret:
        t = []
        t.append(val['city_name'])
        t.append(val['blackout_intervals'])
        ans.append(t)
    return {'cities' : ans}



# city : (x1 , y1)
# sattalite : (x2 , y2)
# step1 : get line
# y = kx + b
# y1 = kx1 + b
# y2 = kx2 + b

# y1 - y2 = k(x1 - x2) => k = (y1 - y2) / (x1 - x2)
# b = y1 - kx1

# step2: find intersection between line and circle
# y = kx + b
# x^2 + y^2 = R^2

# x^2 + (kx + b)^2 = R^2
# (k^2 + 1) * x^2 + (2kb)x + (b^2 - R^2) = 0
# ax^2 + bx + c = 0
# quatratic: