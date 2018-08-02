
def association(data, x, y):
    # association analysis of x->y
    p_x = 0
    p_y = 0
    p_x_INTER_y = 0
    for event in data:
        if (x in event) and (y in event):
            p_x += 1
            p_y += 1
            p_x_INTER_y += 1
        elif x in event:
            p_x += 1
        elif y in event:
            p_y += 1
    p_x = p_x / len(data)
    p_y = p_y / len(data)
    p_x_INTER_y = p_x_INTER_y / len(data)
    support = p_x_INTER_y
    confidence = p_x_INTER_y / p_x
    improvement = confidence / p_y
    print("support     : ", support)
    print("confidence  : ", confidence)
    print("improvement : ", improvement)


if __name__ == "__main__":
    data = [["Bus", "News", "Dict"],
            ["Webtoon", "Metro"],
            ["Metro", "Webtoon", "News"],
            ["Bus", "Metro", "News"],
            ["Webtoon", "Metro"]]
    association(data, "Metro", "Webtoon")
    